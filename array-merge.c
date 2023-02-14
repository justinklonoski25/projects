#include <stdio.h>
#include <stdlib.h>

void merge(int *arr1, int n, int *arr2, int m, int *result) {
  int i = 0, j = 0, k = 0;
  while (i < n && j < m) {
    if (arr1[i] < arr2[j]) {
      result[k++] = arr1[i++];
    } else {
      result[k++] = arr2[j++];
    }
  }
  while (i < n) {
    result[k++] = arr1[i++];
  }
  while (j < m) {
    result[k++] = arr2[j++];
  }
}

int main(void) {
  char filename[100];
  printf("Enter filename: ");
  scanf("%s", filename);
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    printf("File not found.\n");
    return 1;
  }
  int n, m;
  fscanf(fp, "%d", &n);
  int *arr1 = (int *)malloc((size_t)n * sizeof(int));
  for (int i = 0; i < n; i++) {
    fscanf(fp, "%d", &arr1[i]);
  }
  printf("Array1: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr1[i]);
  }
  printf("\nArray1 size: %d\n", n);
  fscanf(fp, "%d", &m);
  int *arr2 = (int *)malloc((size_t)m * sizeof(int));
  for (int i = 0; i < m; i++) {
    fscanf(fp, "%d", &arr2[i]);
  }
  printf("Array2: ");
  for (int i = 0; i < m; i++) {
    printf("%d ", arr2[i]);
  }
  printf("\nArray2 size: %d\n", m);
  int *result = (int *)malloc((size_t)(n + m) * sizeof(int));
  merge(arr1, n, arr2, m, result);
  printf("Combined array: ");
  for (int i = 0; i < n + m; i++) {
    printf("%d ", result[i]);
  }
  printf("\nCombined array size: %d\n", n + m);
  free(arr1);
  free(arr2);
  free(result);
  fclose(fp);
  return 0;
}
