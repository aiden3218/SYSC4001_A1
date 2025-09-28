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
    FILE *executionFile = fopen("executionFile.txt", "w");
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == CPU) {
            fprintf(executionFile, "%i, %i, CPU execution\n", total_time, duration_intr);
            //execution = ("%i, %i, CPU execution\n", total_time, time);
            total_time += duration_intr;
        }
        else if (activity == SYSCALL) {
            fprintf(executionFile, "%i, %i, switch to kernel mode\n", total_time, 1);
            //execution.append("%i, %i, switch to kernel mode\n", total_time, 1);
            total_time += 1;
            fprintf(executionFile, "%i, %i, context saved\n", total_time, 10);
            //execution.append("%i, %i, context saved\n", total_time, 10);
            total_time += 10;
            fprintf(executionFile, "%i, %i, find vector %i in memory position %c\n", total_time, 1, duration_intr, vectors[duration_intr]);
            //execution.append("%i, %i, find vector %i in memory position %i", total_time, 1, duration_intr, vectors[duration_intr]);
            total_time += 1;
        }
        else {

        }


        /************************************************************************/

    }

    fclose(executionFile);

    input_file.close();

    write_output(execution);

    return 0;
}
