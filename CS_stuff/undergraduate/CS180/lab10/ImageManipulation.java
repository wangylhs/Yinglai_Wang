package cs.purdue.lab10;

import android.graphics.Bitmap;
import android.graphics.Color;

public class ImageManipulation {

public static final String user_id = "user_name";
 
 public static Bitmap greyScale(Bitmap b){
	 synchronized(b){
        int height = b.getHeight();
        int width  = b.getWidth();
        for(int x = 0;x<width;x++)
         for(int y=0;y<height;y++){
          int c = b.getPixel(x, y);
          int blue = Color.blue(c);
          int red = Color.red(c);
          int green = Color.green(c);
          int shade = (red + blue + green)/3;
          int intensity = (int)(red*.3 + green*.59 + blue*.11);
          c = Color.argb(intensity,shade,shade,shade);
          b.setPixel(x, y, c);
         }
	 }
  return b;
 }
 
 public static Bitmap leftShift(Bitmap b){
        int height = b.getHeight();
        int width  = b.getWidth();
        for(int x = 0;x<width;x++)
         for(int y=0;y<height;y++){
          int c = b.getPixel(x, y);
          int blue = Color.blue(c);
          int red = Color.red(c);
          int green = Color.green(c);
          c = Color.rgb(blue,red,green);
          b.setPixel(x, y, c);
         }
  return b;
 }
 
 public static Bitmap rightShift(Bitmap b){
        int height = b.getHeight();
        int width  = b.getWidth();
        for(int x = 0;x<width;x++)
         for(int y=0;y<height;y++){
          int c = b.getPixel(x, y);
          int blue = Color.blue(c);
          int red = Color.red(c);
          int green = Color.green(c);
          c = Color.rgb(green,blue,red);
          b.setPixel(x, y, c);
         }
  return b;
 }
 
 public static Bitmap invert(Bitmap b){
        int height = b.getHeight();
        int width  = b.getWidth();
        for(int x = 0;x<width/2;x++)
         for(int y=0;y<height;y++){
          int f = b.getPixel(width-x-1, y);
          int l = b.getPixel(x, y);
          b.setPixel(x, y, f);
          b.setPixel(width-x-1, y, l);
         }
  return b;
 }

}
