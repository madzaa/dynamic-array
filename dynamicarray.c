#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  void** items;
  int length;
  int capacity;
} DA;


DA* DA_new (void) {
  DA* da = malloc(sizeof(DA));
  da->length = 0;
  da->items = malloc(STARTING_CAPACITY * sizeof(void*));
  da->capacity = STARTING_CAPACITY;
  return da;
}
void DA_free(DA *da) {
  free(da->items);
  free(da);
}

int DA_size(DA *da) {
  return da->length;
}

void DA_push (DA* da, void* x) {
  if (da->length >= da->capacity)
  {
    da->capacity = (da->capacity * 2);
    void** new_items = malloc(da->capacity * sizeof(void*));

    for (int i = 0; i < da->length; i++)
    {
      new_items[i] = da->items[i];
    }
    free(da->items);
    da->items = new_items;
  }
  da->items[da->length] = x;
  da->length++;
}

void *DA_pop(DA *da) {
  if (da->length <= 0)
  {
    return NULL;
  }
  da->length--;  
  void *item = da->items[da->length];
  da->items[da->length] = NULL;
  return item;
}

void DA_set(DA *da, void *x, int i) {
  if (i < da->capacity)
  {
    da->items[i] = x;
  }
}

void *DA_get(DA *da, int i) {
  if (da == NULL || da->items == NULL)
  {
    return NULL;
  }
  if (i>=0 && i < da->length)
  {
    return da->items[i];
  }
  return NULL;
  
}

int main() {
    DA* da = DA_new();

    assert(DA_size(da) == 0);

    int x = 5;
    float y = 12.4;
    DA_push(da, &x);
    DA_push(da, &y);
    
    assert(DA_size(da) == 2);
    assert(DA_pop(da) == &y);
    assert(DA_size(da) == 1);

    assert(DA_pop(da) == &x);
    assert(DA_size(da) == 0);
    assert(DA_pop(da) == NULL);

    // basic set/get test
    DA_push(da, &x);
    DA_set(da, &y, 0);
    assert(DA_get(da, 0) == &y);
    DA_pop(da);
    assert(DA_size(da) == 0);

    // expansion test
    DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
    DA_push(da2, &x);
    int i, n = 100 * STARTING_CAPACITY, arr[n];
    for (i = 0; i < n; i++) {
      arr[i] = i;
      DA_push(da, &arr[i]);
    }
    printf("%d\n",DA_size(da));
    assert(DA_size(da) == n);
    for (i = 0; i < n; i++) {
      assert(DA_get(da, i) == &arr[i]);
    }
    for (; n; n--)
      DA_pop(da);
    assert(DA_size(da) == 0);


    assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

    DA_free(da);
    DA_free(da2);
    printf("OK\n");
}
