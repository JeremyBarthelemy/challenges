
#include <iostream>



int main(int argc, char* argv[])
{
    std::cout << "hello!" << std::endl;


    if (argc == 1)
    {
        std::cout << "Just one file." << std::endl;

    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {

            std::cout << "additional file: " << i << std::endl;
        }
    }

    return 0;
}

