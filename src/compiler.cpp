#include "compiler.h"
#include <ctime>
#include <string>

Compiler::Compiler() { }

Compiler::~Compiler() { }

void Compiler::run(const std::string &sourceFileName) {
    std::string inputFilePath = "input/";
    std::string outputFileName, outputFilePath = "output/";

    std::cout << "checking name.." << std::endl;
    if (!hasFileExtension(sourceFileName, "txt")) {
        throw std::runtime_error("Error: Source file does not have a .txt extension.\n");
    }

    std::cout << "good name, opening!" << std::endl;
    inputFilePath.append(sourceFileName);
    inputFile.open(inputFilePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Source file could not be opened.\n");
    }

    std::cout << "still opening one sec..." << std::endl;
    outputFileName = getFormattedDate("%m-%d-%Y_%H-%M-%S") + ".txt";
    outputFilePath.append(outputFileName);
    outputFile.open(outputFilePath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Results file could not be opened.\n");
    }

    std::cout << "Tokenizing..." << std::endl;
    Lexer lexer(inputFile, outputFile, tokens);
    lexer.tokenize();
    lexer.writeTokensToFile();

    std::cout << "Parsing..." << std::endl;
    Parser parser(outputFile, tokens);
    parser.parse();
    
    std::cout << "Results file should be in: " << outputFileName << std::endl;
    outputFile.close();
    inputFile.close();
}

std::string Compiler::getFormattedDate(const std::string &format) {
    time_t rawTime;
    struct tm* timeInfo;
    char timeCStr[500];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    // Use "%Y-%m-%d" format to get the date portion only
    strftime(timeCStr, 500, "%Y-%m-%d", timeInfo);

    std::string date(timeCStr);

    return date;
}

bool Compiler::hasFileExtension(const std::string &fileName, const std::string &fileExtension) {
    size_t extensionIndex = fileName.find_last_of(".");
    std::string extension = fileName.substr(extensionIndex + 1);
    
    if (extensionIndex == std::string::npos) {
        return false;
    }
    
    if (extension != fileExtension) {
        return false;
    }
    
    return true;
}