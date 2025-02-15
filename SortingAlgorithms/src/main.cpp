#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <imgui-SFML.h>
#include <imgui.h>
#include <random>
#include <algorithm>
#include "Algorithm.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"

int main(int argc, char const *argv[])
{
    unsigned int width, height;
    width = sf::VideoMode::getFullscreenModes()[0].width;
    height = sf::VideoMode::getFullscreenModes()[0].height;
    sf::RenderWindow window(sf::VideoMode(width, height), "Sorting Algorithms", sf::Style::Fullscreen);
    width = window.getSize().x;
    height = window.getSize().y;

    int size = 100;
    std::vector<int> values(size);
    std::mt19937 randomGen;
    randomGen.seed((int)time(0));

    for (int i = 1; i <= size; i++)
        values[i - 1] = i;
    std::shuffle(values.begin(), values.end(), randomGen);

    ImGui::SFML::Init(window, true);
    sf::Clock clk;

    sf::View view;
    sf::RectangleShape drawingShape;
    float widthStep = (float)width / (float)size;
    if ((float)size > width)
        widthStep = 1.0f;
    else
    {
        widthStep = std::max((float)width / (float)size, 1.0f);
    }
    view.setSize(sf::Vector2f(widthStep * size, ((float)width / (float)height) * widthStep * size));
    view.setCenter(view.getSize().x / 2.0f, view.getSize().y / 2.0f);
    drawingShape.setSize(sf::Vector2f(widthStep, height * ((float)size / (float)size)));
    drawingShape.setOutlineThickness(1.0f);
    drawingShape.setOutlineColor(sf::Color::Green);
    bool running = false;
    std::vector<Algorithm *> algorithms;
    algorithms.push_back((Algorithm *)new BubbleSort(values));
    algorithms.push_back((Algorithm *)new InsertionSort(values));
    algorithms.push_back((Algorithm *)new SelectionSort(values));
    Algorithm *currentAlgorithm = nullptr;

    std::string windowName = "Algorithms Menu";
    float delay = 0.0f;
    float totalTime = 0.0f;
    while (window.isOpen())
    {
        sf::Time dt = clk.restart();
        totalTime += dt.asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        ImGui::SFML::Update(window, dt);
        ImGui::Begin("Test Menu");
        ImGui::TextUnformatted(windowName.c_str());
        if (currentAlgorithm == nullptr)
        {
            for (int i = 0; i < algorithms.size(); i++)
            {
                if (ImGui::Button(algorithms[i]->name.c_str()))
                {
                    currentAlgorithm = algorithms[i];
                    windowName = currentAlgorithm->name;
                    break;
                }
            }
        }
        else
        {
            if (ImGui::Button("<-"))
            {
                currentAlgorithm->Reset();
                currentAlgorithm = nullptr;
                windowName = "Algorithms Menu";
            }
            ImGui::Checkbox("Running", &running);
            ImGui::TextUnformatted("Delay:");
            ImGui::SameLine();
            ImGui::SliderFloat("###2", &delay, 0.0f, 2.0f);
            ImGui::TextUnformatted("Max Num:");
            ImGui::SameLine();
            ImGui::SliderInt("###3", &size, 10, 10000);
            if (ImGui::Button("Recreate"))
            {
                values.clear();
                values.resize(size);
                for (int i = 1; i <= size; i++)
                    values[i - 1] = i;
                std::shuffle(values.begin(), values.end(), randomGen);
                if ((float)size > width)
                    widthStep = 1.0f;
                else
                {
                    widthStep = std::max((float)width / (float)size, 1.0f);
                }
                view.setSize(sf::Vector2f(widthStep * size, ((float)width / (float)height) * widthStep * size));
                view.setCenter(view.getSize().x / 2.0f, view.getSize().y / 2.0f);
                drawingShape.setSize(sf::Vector2f(widthStep, (float)height));

                if (currentAlgorithm)
                    currentAlgorithm->Reset();
                running = false;
            }
        }
        ImGui::End();
        if (currentAlgorithm && !currentAlgorithm->Finished() && running && (totalTime - delay) >= 0)
        {
            currentAlgorithm->SolveStep();
            totalTime = 0.f;
        }

        window.setView(view);
        window.clear();
        for (int i = 0; i < values.size(); i++)
        {
            drawingShape.setSize(sf::Vector2f(widthStep, view.getSize().y * ((float)values[i]) / (float)values.size()));
            drawingShape.setPosition(sf::Vector2f(i * widthStep, view.getSize().y - drawingShape.getSize().y));
            if (currentAlgorithm && (i == currentAlgorithm->lastChangeIndex1 || i == currentAlgorithm->lastChangeIndex2))
                drawingShape.setFillColor(sf::Color::Blue);
            else
                drawingShape.setFillColor(sf::Color::White);
            window.draw(drawingShape);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
