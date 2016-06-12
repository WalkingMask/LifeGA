import java.util.ArrayList;

public class LifeGA
{
    // variables
    private int maxNumPopuls;
    private ArrayList<Item> phenotype = new ArrayList<Item>();

    private ArrayList<Individual> indivs = new ArrayList<Individual>();    // the entity of the individuals
    private int numIndivs;                                                 // the number of the existed individuals
    private ArrayList<Integer> indivNums = new ArrayList<Integer>();       // the used numbers of the individual
    private ArrayList<Integer> vacantIndivNums = new ArrayList<Integer>(); // the vacant numbers of the individual

    private ArrayList<Population> populs = new ArrayList<Population>(); // the entity of the populations
    private int numPopuls;                                              // the number of the existed populations
    private boolean populNums[];                                        // the used numbers of the population
    private boolean vacantPopulNums[];                                  // the vacant numbers of the population

    // constructor
    LifeGA(int maxnp, ArrayList<Item> items)
    {
        this.maxNumPopuls = maxnp;
        this.phenotype = items;
        this.numIndivs = 0;
        this.numPopuls = 0;
        this.populNums = new boolean[maxNumPopuls];
        this.vacantPopulNums = new boolean[maxNumPopuls];
    }

    // functions
    public void initialize()
    {
        int i;
        // initialize the vacant array
        for (i=0; i<this.maxNumPopuls; i++) {
            this.populNums[i] = false;
            this.vacantPopulNums[i] = true;
        }

        // create the first populations
        int x = 2; // it must be random
        for (i=0; i<x; i++) {
            int initPopulNum = i*50+1; // it must be random
            Population popul = new Population(initPopulNum);
            addPopul(popul);
        }

        // create the first individuals
        for (Population popul: populs) {
            System.out.println(popul.populNum);
            int y = 4; // it must be random
            for (i=0; i<y; i++) {
                int initIndivNum = popul.populNum + i; // it must be follow the indivNums of vacant
                Individual indiv = new Individual(initIndivNum,popul.populNum,true,-999,1,1,1,1);
                addIndiv(indiv, initIndivNum);
            }
        }

        // test print
        for (Individual indiv: indivs) {
            indiv.printIndiv();
        }
    }

    private void addPopul(Population popul)
    {
        this.populs.add(popul);
        this.vacantPopulNums[popul.populNum] = false;
        this.populNums[popul.populNum] = true;
        this.numPopuls++;
    }

    private void removePopul(Population popul)
    {
        this.populs.remove( populs.indexOf(popul) );
        this.vacantPopulNums[popul.populNum] = true;
        this.populNums[popul.populNum] = false;
        this.numPopuls--;
    }

    private void addIndiv(Individual indiv, int indivNum)
    {
        this.indivs.add(indiv);
        this.indivNums.add(indivNum);
        if ( this.vacantIndivNums.indexOf(indivNum) != -1)
            this.vacantIndivNums.remove( this.vacantIndivNums.indexOf(indivNum) );
        this.numIndivs++;
    }

    private void removeIndiv(Individual indiv, int indivNum)
    {
        this.indivs.remove( this.indivs.indexOf(indiv) );
        this.indivNums.remove( this.indivNums.indexOf(indivNum) );
        this.vacantIndivNums.add(indivNum);
        this.numIndivs--;
    }
}