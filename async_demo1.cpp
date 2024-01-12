#include<future>
#include<iostream>
    /*
    data will be read on future 
    jo party data consume krgi -->future
    jo party provide value -->promise
    */
/*
    A   B   C

    Suppose there are 3 tasks

    options 1 : one after the other. Always complete one thing before
                starting the next task

            Name :    single thread technique
    //////////////////////////////////////////////////////////
    option 2 : I will complete all task in such a way that I "practically start all of them at
                same time" but keep juggling them based on some criteria

            Name :    multi thread approach
    /////////////////////////////////////////////////////////////
    options 3 : map number of task amongst number of available "workers" 

            Name :    Parallel Execution
    //////////////////////////////////////////////////////////////

    options 4 : Start a task. Either delegate it to another worker OR do it
                yourself after some time.

                If somemone else is doing a task, monitor it, wait for their work to be done, 
                take follow-p actions accordingly.  

            Name : Asynchronous execution
*/

/*
    2 tasks
    Calculate Factorial of 5 
    Calculate square of a number given by the user
*/

int square(std::future<int>& ft )
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square. I have started my work.\n";
    int number = ft.get();
    return number*number;
}

int factorial(int number )
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number < 0)
        throw std::runtime_error("The number is negative.");

   else if(number == 0 || number == 1)
    {
        return 1;
    }

    else {
        return number*factorial(number -1);
    }
}

int main()
{
    //step -1 : make a pomise 
    std::promise<int> pr;
    
   
    //step 2 : A future linked to a promise
    std::future<int> ft = pr.get_future();
    
    
    /*
        OS : launch square (if possible a new thread)
    */
   //async will launch the thread (square)
   std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));
//Here the code will get ahead by main.

    std::cout<<factorial(5);
    int val =0;
    std::cin>>val;
    pr.set_value(val);
    std::cout<< "Result of factorial is: "<<result_ft.get();

    //factorial is a main thread and square can be a another thread 
    // there is no special thread for factorial
}

/*
        Clinet-Server Architecture

        Future-promise model :
            //Two task tow thread two entities can talk to each other

        square calculation 

        Main needs to delegate the task of square calculation 

        -----> A new thread for square will be registered with os.


*/




/*
    In asynchrnous program there are events
    We have to write our code in regards of this event. 

*/