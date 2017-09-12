class List {
    public List(List next) {
        this.next = next;
        if (next == null) {
            this.value = 0;
        } else {
            this.value = next.value + 1;
        }
    }

    public List next;
    public long value;
}
