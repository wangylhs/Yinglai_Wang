class Arrays {
    public static final int count = 10000000;

    public static void main(String[] args) {
        int i, rep, res;
        int[] ints = new int[count];
        for (i = 0; i < count; i++) {
            ints[i] = i;
        }
        res = 0;
        for (rep = 0; rep < 10; rep++) {
            for (i = 0; i < count; i++) {
                res += ints[i];
            }
        }
        System.out.println(res);
    }
}
