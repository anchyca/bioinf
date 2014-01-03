public class proba {

private static int[] findLis(int[] arr) {
    int[] is = new int[arr.length];
    int index = 0;
    is[0] = index;

    for (int i = 1; i < arr.length; i++) {
        if (arr[i] < arr[is[index]]) {
            for (int j = 0; j <= index; j++) {
                if (arr[i] < arr[is[j]]) {
                    is[j] = i;
                    break;
                }
            }
        } else if (arr[i] == arr[is[index]]) {

        } else {
            is[++index] = i;
        }
    }

    int[] lis = new int[index + 1];
    lis[index] = arr[is[index]];

    for (int i = index - 1; i >= 0; i--) {
        if (is[i] < is[i + 1]) {
            lis[i] = arr[is[i]];
        } else {
            for (int j = is[i + 1] - 1; j >= 0; j--) {
                if (arr[j] > arr[is[i]] && arr[j] < arr[is[i + 1]]) {
                    lis[i] = arr[j];
                    is[i] = j;
                    break;
                }
            }
        }
    }

    return lis;
}

public static void main(String[] args) {
	long startTime = System.currentTimeMillis();

    int[] arr = new int[] { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
    for (int i : findLis(arr)) {
        System.out.print(i + "-");
    }
    System.out.println();
    long estimatedTime = System.currentTimeMillis() - startTime;
    System.out.println("vrijeme " + estimatedTime);

    arr = new int[] { 1, 9, 3, 8, 11, 4, 5, 6, 4, 19, 7, 1, 7 };
    for (int i : findLis(arr)) {
        System.out.print(i + "-");
    }
    System.out.println();

}
}