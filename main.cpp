#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief consolidateSequences Helper function that takes text and returns a vector of all words in sequences found in it
 * @param text The text to analyze
 * @return Returns all three word sequences for given text input
 */
std::vector<std::wstring> consolidateSequences(const std::wstring& text)
{
    std::wstring word;
    std::vector<std::wstring> words;
    for (wchar_t c : text)
    {
        c = std::towlower(c);

        // Replace quotation marks with spaces ( U+201C = left double quotation mark, and U+201D = right double quotation mark
        if (c == L'"' || c == L'\u201C' || c == L'\u201D')
        {
            c = L' ';
        }

        if (iswalnum(c) || c > 127)
        {
            word += c;
        }
        else if (c == L' ' || c == L'\n')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

/**
 * @brief generateTrigramMap Produces a map of all of the three word sequences (trigrams) found inside of the provided data
 * @param data Data to pull three word sequences from
 * @param trigramMap The map containing sequences as keys with their number of occurrences as the value associated with each sequence
 */
void generateTrigramMap(
        const std::wstring& data,
        std::map<std::wstring, int>& trigramMap)
{
    std::vector<std::wstring> words = consolidateSequences(data);
    for (size_t i = 0; i < words.size() - 2; ++i) // Note: words.size() -2 so we don't go out of vector bounds on last sequence!
    {
        std::wstring sequence = words[i] + L" " + words[i + 1] + L" " + words[i + 2];

        // Increment sequence counter associated with each trigram
        trigramMap[sequence]++;
    }
}

/**
 * @brief sortTrigrams Sorts (and prints) the trigrams captured from the input data
 * @param trigramMap The unsorted trigram map, which will then be sorted and printed in descending order
 *                   from the most occurrences to the fewest
 */
void sortTrigrams(const std::map<std::wstring, int>& trigramMap)
{
    std::vector<std::pair<std::wstring, int>> sortedTrigrams(trigramMap.begin(), trigramMap.end());
    std::sort(sortedTrigrams.begin(), sortedTrigrams.end(), [](const auto &a, const auto &b)
    {
        return a.second > b.second;
    });

    // Display top 100 (or fewer) entries in sorted Trigram map
    for (size_t i = 0; i < sortedTrigrams.size() && i < 100; ++i)
    {
        std::wcout << sortedTrigrams[i].first << L": " << sortedTrigrams[i].second << std::endl;
    }
}

void runAllTests()
{
    // Basic test
    {
        std::wstring test = L"I love sandwiches.";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"i", L"love", L"sandwiches"}));
    }

    // Multiple spaces
    {
        std::wstring test = L"I   love         sandwiches";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"i", L"love", L"sandwiches"}));
    }

    // Quotes, newline
    {
        std::wstring test = L"\"I love\nsandwiches?\"";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"i", L"love", L"sandwiches"}));
    }

    // All caps
    {
        std::wstring test = L"I LOVE SANDWICHES!!";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"i", L"love", L"sandwiches"}));
    }

    // Accept beyond regular ascii set for chars with accents
    {
        std::wstring test = L"Prince Vasíli Kurágin";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"prince", L"vasíli", L"kurágin"}));
    }

    // Punctuation and curly quotes
    {
        std::wstring test = L"“Sandwiches,” he said";
        std::vector<std::wstring> result = consolidateSequences(test);
        assert((result == std::vector<std::wstring>{L"sandwiches", L"he", L"said"}));
    }

    std::cout << "All tests passed!" << std::endl;
}

int main(int argc, char* argv[])
{
    // Set locale for alphanumeric parsing to not skip letters with accents in them
    // Need this for the iswalnum() check (e.g. for "Prince Vasíli Kurágin")
    std::locale::global(std::locale(""));

    // Map with key = trigrams (three word sequences) and value of the number of sequence hits encountered in file
    std::map<std::wstring, int> trigramMap;

    if (argc == 1)
    {
        // Read from stdin
        std::wstring textData, line;
        while (std::getline(std::wcin, line))
        {
            textData += line + L" ";
        }
        generateTrigramMap(textData, trigramMap);
    }
    else
    {
        // Run the tests
        if (argc == 2 && (std::string)argv[1] == "RunAllTests")
        {
            runAllTests();
            return 0;
        }

        // Perform text analysis
        for (int i = 1; i < argc; ++i)
        {
            std::wifstream file(argv[i]);
            if (!file.is_open())
            {
                std::cout << "Could not find file: " << argv[i] << "!" << std::endl;
                continue;
            }

            // Read the entire file content at once
            std::wstringstream stream;
            stream << file.rdbuf();

            file.close();
            generateTrigramMap(stream.str(), trigramMap);
        }
    }

    sortTrigrams(trigramMap);

    return 0;
}
