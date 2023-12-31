#include <fstream>

#include "SolutionBase.h"
#include "fmt/printf.h"


void SolutionBase::Run(const int example1Result, const int example2Result)
{
    if (DayNum() < 1 || DayNum() > 25)
    {
        fmt::println(stderr, "DayNum should be from 1 to 25 (got {})", DayNum());
        std::exit(1);
    }

    SolveExample(1, example1Result, &SolutionBase::Part1);
    SolveInput(1, &SolutionBase::Part1);
    fmt::println("------------------------------");
    SolveExample(2, example2Result, &SolutionBase::Part2);
    SolveInput(2, &SolutionBase::Part2);
}

void SolutionBase::SolveInput(const int partNum, const SolutionPartFunction partFunc)
{
    const std::vector<std::string> inputLines = readFileLines(-1);

    const auto begin1 = std::chrono::high_resolution_clock::now();
    int result = (this->*partFunc)(inputLines);
    const auto end1 = std::chrono::high_resolution_clock::now();

    if (result > 0)
    {
        fmt::println("Day {}, part {} result: {} completed in {:.2f} ms", DayNum(), partNum, result,
                     std::chrono::duration<double, std::milli>(end1 - begin1).count());
    }
    else
    {
        fmt::println("Day {}, part {} not implemented", DayNum(), partNum);
    }
}

void SolutionBase::SolveExample(const int exampleNum, const int expectedResult, const SolutionPartFunction partFunc)
{
    const std::vector<std::string> exampleLines = readFileLines(exampleNum);

    if (int result = (this->*partFunc)(exampleLines); result >= 0)
    {
        if (result == expectedResult)
        {
            fmt::println("Day {}, example {} result: {} (OK)", DayNum(), exampleNum, result);
        }
        else
        {
            fmt::println(stderr, "ERROR day {} example {}, expected: {} received: {}",
                         DayNum(), exampleNum, expectedResult, result);
            std::exit(1);
        }
    }
    else
    {
        fmt::println("Day {}, example {} not implemented", DayNum(), exampleNum);
    }
}

std::vector<std::string> SolutionBase::readFileLines(const int exampleNum)
{
    std::string dayStr = std::to_string(DayNum());

    // day 1-9 should be 0X
    if (DayNum() <= 9)
    {
        dayStr = "0" + dayStr;
    }

    std::string fileName;
    if (exampleNum >= 0)
    {
        fileName = fmt::format("example_{}.txt", exampleNum);
    }
    else
    {
        fileName = "input.txt";
    }

    std::string inputPath = fmt::format("inputs/day_{}/{}", dayStr, fileName);

    if (!std::filesystem::exists(inputPath))
    {
        fmt::println(stderr, "Cannot find '{}'", inputPath);
        std::exit(1);
    }

    std::ifstream ifs {inputPath};
    std::vector<std::string> lines;
    std::string line;
    while(std::getline( ifs, line ))
        lines.push_back(std::move(line));

    return lines;
}
