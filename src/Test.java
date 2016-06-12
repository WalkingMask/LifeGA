import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

public class Test
{
    final static int guiWidth     = 600;
    final static int guiHeight    = 400;
    final static int maxNumPopuls = guiWidth*guiHeight;
    final static String filename  = "../items.txt";

    public static void main(String[] args)
    {
        // the test field here
        System.out.println("Hello World!");
        System.out.println( Integer.toBinaryString(100) );

        // set the item list from the file
        ArrayList<Item> items = new ArrayList<Item>();
        setItemList(filename, items, 10);
        /*
        // test print
        for (Item item: items) {
            System.out.println(item.price+","+item.weight);
        }
        */

        // pass the item list to LifeGA
        LifeGA lifega = new LifeGA(maxNumPopuls, items);

        // initialize the LifeGA
        lifega.initialize();
    }

    static void setItemList(String filename, ArrayList<Item> items, int num)
    {
        try {

            File fp = new File(filename);
            BufferedReader br = new BufferedReader(new FileReader(fp));

            String str;
            for (int i=0; i<num; i++) {
                str = br.readLine();
                if (str == null)
                    break;
                String[] s = str.split(",", 0);
                Item item = new Item( Integer.parseInt(s[0]), Integer.parseInt(s[1]) );
                items.add(item);
            }

            br.close();

        } catch(FileNotFoundException e) {
            System.out.println(e);
        } catch(IOException e) {
            System.out.println(e);
        }
    }
}