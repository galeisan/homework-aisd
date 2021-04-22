import java.io.*;
import java.util.*;

public class Qt {
    public static void main(String[] args) throws IOException{
        FileOutputStream fos = new FileOutputStream("output2.txt");
        PrintWriter pw = new PrintWriter(fos);
        String alp = "ics";
        for (int i=0; i<50; i++) {
            int n = 100 + (int) (Math.random() * (10000 - 100 + 1));
            pw.print(n + " ");
            for (int j = 0; j < n; j++) {
                int fill = (int) (Math.random() * (1000 + 1)); //заполняем элементы
                pw.print(fill + " ");
            }
            int numb = (int) (Math.random() * (1000 + 1));
            pw.println(numb);
            pw.println();
        }
        pw.close();
    }
}
