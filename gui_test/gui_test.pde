
import java.util.Random;

public static int frame_s;
public static int disp_s;
public static int dot_w, dot_h;

void setup()
{ 
  size(620, 440);

  frame_s = 10;
  disp_s = 20;
  dot_w = width - frame_s*2;
  dot_h = height - frame_s*2 - disp_s;

}

void draw()
{
  background(255); // white
  
  Random rnd = new Random();
  
  int i, j;
  for (i=0; i<=dot_w; i++) {
    for (j=0; j<=dot_h; j++) {
      stroke(rnd.nextInt(256)-1, rnd.nextInt(256)-1, rnd.nextInt(256)-1);
      point(frame_s+i, frame_s+j);
    }
  }
}