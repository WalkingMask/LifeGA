import java.util.ArrayList;

public class Population
{
    // variables
    int populNum; // identification number of the population
    ArrayList<Integer> indivNums; // the numbers of the belonging individuals

    int maxFitParam;
    int aveFitParam;
    int resources;

    Population(int populNum)
    {
        this.populNum = populNum;
    }
}