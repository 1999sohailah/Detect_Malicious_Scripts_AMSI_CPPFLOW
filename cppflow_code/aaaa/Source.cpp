#include <iostream>
#include <stdio.h>
//#include <tensorflow/c/c_api.h>
#include <cppflow/cppflow.h>
#include <fstream>
#include <sstream>
//#include <tensorflow/c/c_api.h>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
#include "rpc/server.h"

using namespace std;

cppflow::model model("C:\\Users\\Administrator\\Desktop\\AMSI_GP\\Sequential_model");

int model_calc(std::string input) {

    std::vector<std::string> sent1 = {input};

    auto sentence = cppflow::tensor(sent1, { 1 });


    // Run
    auto output = model(sentence);


    // Show the predicted class
    //std::cout << "HelloOOOO\n";
    float f = output.get_data<float>()[0];
    std::cout << f << "\n";


    return (int)f;
}



int main(int argc, char* argv[]) {
        // Creating a server that listens on port 8080
        rpc::server srv(8080);

        // Binding a lambda function to the name "add".
        srv.bind("model_calc", [](std::string model_input) {
            std::cout << model_input;
            int model_output = model_calc(model_input);
            return model_output;
            });

        // Run the server loop.
        srv.run();
        
        return 0;
}
    
    
