/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    std::string CPU = "CPU";
    std::string SYSCALL = "SYSCALL";
    std::string ENDIO = "END_IO";
    int total_time = 0;
    int time = 0;
    std::pair<std::string, int> myPair = std::make_pair(execution, total_time);
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == CPU) {
            execution += std::to_string(total_time) + ", " + std::to_string(duration_intr) + ", CPU burst\n";
            total_time += duration_intr;
        }
        else if (activity == SYSCALL) {
            myPair = intr_boilerplate(total_time, duration_intr, 10, vectors);
            execution += myPair.first;
            total_time = myPair.second;

            execution += std::to_string(total_time) + ", " + std::to_string(delays[duration_intr]) + ", ISR to call device driver\n";
            total_time += delays[duration_intr];

            execution += std::to_string(total_time) + ", " + std::to_string(1) + ", IRET\n";
            total_time += 1;

            execution += std::to_string(total_time) + ", " + std::to_string(1) + ", switch to user mode\n";
            total_time += 1;

            execution += std::to_string(total_time) + ", " + std::to_string(10) + ", context restored\n";
            total_time += 10;

        }
        else if (activity == ENDIO){
            myPair = intr_boilerplate(total_time, duration_intr, 10, vectors);
            execution += myPair.first;
            total_time = myPair.second;

            execution += std::to_string(total_time) + ", " + std::to_string(delays[duration_intr]) + ", END_IO execution\n";

            execution += std::to_string(total_time) + ", " + std::to_string(1) + ", switch to user mode\n";
            total_time += 1;

            execution += std::to_string(total_time) + ", " + std::to_string(10) + ", context restored\n";
            total_time += 10;
        }


        /************************************************************************/

    }

    input_file.close();


    write_output(execution);

    return 0;
}
