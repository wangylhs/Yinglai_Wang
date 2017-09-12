class ListMain {
    public static void main(String[] args) {
        List cur = new List(null);
        while (true) {
            cur = new List(cur);
            if ((cur.value % 100000) == 0) {
                System.out.println(cur.value);
            }
        }
    }
}
