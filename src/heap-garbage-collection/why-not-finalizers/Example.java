class Example {

    protected void finalize () {
        System.out.println ("Finalize called ...");
    }

    void work () {
        System.out.println ("Work called ...");
        for (int i = 0 ; i < 1000000 ; i++) {
            if (i % 10000 == 0) {
                System.out.println (i);
                System.gc ();
            }
        }
        System.out.println ("Work returning ...");
    }

    public static void main (String [] args) {
        new Example ().work ();
    }
}
