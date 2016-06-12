import java.io.*;

public class Main
{
    final int guiWidth    = 600;
    final int guiHeight   = 400;
    final int maxNumPopul = guiWidth*guiHeight;

    public static void main(String[] args)
    {
        System.out.println("Hello World!");

        List<Item> items = new List<Item>();
        setItemList("../items.txt", items, 10);
    }

    void setItemList(String filename, List<Item> items, int num)
    {
        try {

            File fp = new File(filename);

            if ( checkBeforeReadfile(fp) ) {

                BufferedReader br = new BufferedReader(new FileReader(fp));

                String str;
                for (int i=0; i<num; i++) {
                    str = br.readLine();
                    if (str == null) break;
                    System.out.println(str);
                }

                br.close();

            } else
                System.out.println("error! the file could not open.");

        } catch(FileNotFoundException e) {
            System.out.println(e);
        } catch(IOException e) {
            System.out.println(e);
        }
    }
}

public class Item
{
    public int price;
    public int weight;

    Item(int p, int w)
    {
        this.price = p;
        this.weight = w;
    }
}
