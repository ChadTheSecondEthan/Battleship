void timedelay(unsigned long millis)
{
    clock_t startTime = clock();

    while(clock() < startTime + millis);
}