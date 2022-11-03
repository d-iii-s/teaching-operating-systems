class Example {

    private static final int SIZE_CHECK_PERIOD = 1000;
    private static final double FREE_SPACE_SLACK = 0.1;

    static class Payload {
        int i0;
        int i1;
        Payload p0;
        int i2;
        int i3;
        int i4;
        Payload p1;
        int i5;
        int i6;
        int i7;
        Payload p2;
        int i8;
        int i9;
    }

    public static volatile Payload initial = new Payload ();

    public static void main (String [] args) {
        Runtime runtime = Runtime.getRuntime ();
        Payload latest;

        System.out.println ("Allocating ...");
        long slack = Math.round (runtime.maxMemory () * FREE_SPACE_SLACK);
        latest = initial;
        while (true) {
            for (int i = 0 ; i < SIZE_CHECK_PERIOD ; i ++) {
                Payload extension = new Payload ();
                extension.p1 = new Payload ();
                extension.p2 = new Payload ();
                latest.p0 = extension;
                latest = extension;
            }
            if (runtime.maxMemory () - runtime.totalMemory () + runtime.freeMemory() < slack) {
                break;
            }
        }

        System.out.println ("Pruning ...");
        latest = initial;
        while (latest != null) {
            latest.p1 = null;
            latest.p2 = null;
            latest = latest.p0;
        }

        System.out.println ("Collecting ...");
        long used_before = runtime.totalMemory () - runtime.freeMemory ();
        long time_before = System.nanoTime ();
        System.gc ();
        long time_after = System.nanoTime ();
        long used_after = runtime.totalMemory () - runtime.freeMemory ();
        System.out.println ("Collected " + (used_before - used_after) / 1e9 + " GB of " + used_before / 1e9 + " GB in " + (time_after - time_before) / 1e9 + " seconds");
    }
}
