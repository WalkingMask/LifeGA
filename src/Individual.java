public class Individual
{
    private int indivNum;
    private int populNum;
    private int partnerNum;

    private boolean sex;
    private long chrom; // this has 64 genes
    private int totalWeight;
    private int totalPrice;
    private int fitness;
    private int lifespan;

    // there is 8 parameters
    Individual(int indivNum, int populNum, boolean sex, long chrom,
        int totalW, int totalP, int fitness, int lifespan)
    {
        this.indivNum = indivNum;
        this.populNum = populNum;
        this.partnerNum = 0;
        this.sex = sex;
        this.chrom = chrom;

        this.totalWeight = totalW;
        this.totalPrice  = totalP;
        this.fitness  = fitness;
        this.lifespan = lifespan;
    }

    // getter
    public int getIndivNum() { return this.indivNum; }
    public int getPopulNum() { return this.populNum; }
    public int getPartnerNum() { return this.partnerNum; }
    public boolean getSex() { return this.sex; }
    public long getChrom() { return this.chrom; }
    public int getTotalWeight() { return this.totalWeight; }
    public int getTotalPrice() { return this.totalPrice; }
    public int getFitness() { return this.fitness; }
    public int getLifespan() { return this.lifespan; }

    // setter
    public void setPartnerNum(int partnerNum) { this.partnerNum = partnerNum; }
    public void setLifespan(int lifespan) { this.lifespan = lifespan; }

    // print
    public void printIndiv()
    {
        System.out.println("indivNum: "+this.indivNum);
        System.out.println("populNum: "+this.populNum);
        System.out.println("partnerNum: "+this.partnerNum);
        if (sex)
            System.out.println("sex: osu");
        else
            System.out.println("sex: mesu");
        System.out.println("total weight: "+this.totalWeight);
        System.out.println("total price: "+this.totalPrice);
        System.out.println("fitness: "+this.fitness);
        System.out.println("lifespan: "+this.lifespan);
        System.out.println("chrom: ");
        System.out.println( Long.toBinaryString(this.chrom) );
    }
}