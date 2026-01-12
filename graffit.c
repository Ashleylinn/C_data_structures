/**
 * CSC A48 - Intro to Computer Science II
 * 
 * Assignment 3 - Graffit 
 * 
 * This is the file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) William Song, Mustafa Quraish
 * (c) Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE]; 
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{
  for(FriendNode *p = allUsers; p != NULL; p = p->next)
  {
    if(strcmp(p->user->name, name) == 0)
      return NULL;
  }

  User *new_user = (User *)calloc(1, sizeof(User));
  strcpy(new_user->name, name);
  new_user->friends = NULL;
  new_user->brands = NULL;
  new_user->visited = false;

  FriendNode *new_node = (FriendNode *)calloc(1, sizeof(FriendNode));
  new_node->user = new_user;
  new_node->next = NULL;

  if(allUsers == NULL || strcmp(name, allUsers->user->name) < 0)
  {
    new_node->next = allUsers;
    allUsers = new_node;
  }
  else
  {
    FriendNode *q = allUsers;
    while(q->next != NULL && strcmp(name, q->next->user->name) > 0)
    {
      q = q->next;
    }
    new_node->next = q->next;
    q->next = new_node;
  }
  
  return new_user;
}

/**
 * TODO: Complete this function
 * Deletes a given user.
 */
int delete_user(User *user)
{
  if(user == NULL)
    return -1;
  
  FriendNode *pre = NULL;
  FriendNode *curr = allUsers;
  while(curr != NULL)
  {
    if(curr->user == user)
    {
      if(pre == NULL)
      {
        allUsers = curr->next;
      }
      else
      {
        pre->next = curr->next;
      }
      free(curr);
      break;
    }
    pre = curr;
    curr = curr->next;
  }

  for(curr = allUsers; curr != NULL; curr = curr->next)
  {
    curr->user->friends = delete_from_friend_list(curr->user->friends, user);
  }
  free(user);
  return 0;
}

/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
  if(user == NULL || friend == NULL || in_friend_list(user->friends, friend))
  {
    return -1;
  }
  user->friends = insert_into_friend_list(user->friends, friend);
  friend->friends = insert_into_friend_list(friend->friends, user);
  return 0;
}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
  if(user == NULL || friend == NULL)
    return -1;
  
  if(in_friend_list(user->friends, friend) == false)
    return -1;
  
  user->friends = delete_from_friend_list(user->friends, friend);
  friend->friends = delete_from_friend_list(friend->friends, user);
  return 0;
}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{
  if(user == NULL || brand_name == NULL || in_brand_list(user->brands, brand_name))
    return -1;
  
  int index = get_brand_index(brand_name);
  if(index == -1)
    return -1;
  
  user->brands = insert_into_brand_list(user->brands, brand_name);
  return 0;
}

/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
  if(user == NULL || brand_name == NULL)
    return -1;
  
  if(in_brand_list(user->brands, brand_name) == false)
    return -1;
  
  user->brands = delete_from_brand_list(user->brands, brand_name);
  return 0;
}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{
  if(a == NULL || b == NULL)
    return -1;
  
  int count = 0;
  FriendNode *p = a->friends;
  while(p != NULL)
  {
    if(in_friend_list(b->friends, p->user))
    {
      count++;
    }
    p = p->next;
  }

  return count;
}

/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */
int get_degrees_of_connection(User *a, User *b)
{
  if(a == NULL || b == NULL)
    return -1;

  if(strcmp(a->name, b->name) == 0)
    return 0;
  
  for(FriendNode *p = allUsers; p != NULL; p = p->next)
  {
    p->user->visited = false;
  }

  int degree = 0;
  FriendNode *node = NULL;
  node = insert_into_friend_list(node, a);
  a->visited = true;

  while(node != NULL)
  {
    degree++;
    FriendNode *node2 = NULL;
    for(FriendNode * q = node; q != NULL; q = q->next)
    {
      User *user = q->user;
      for(FriendNode *f = user->friends; f != NULL; f = f->next)
      {
        if(f->user == b)
        {
          while(node != NULL)
          {
            FriendNode *tmp = node;
            node = node->next;
            free(tmp);
          }
          return degree;
        }
        if(f->user->visited == false)
        {
          node2 = insert_into_friend_list(node2, f->user);
          f->user->visited = true;
        }
      }
    }
    while(node != NULL)
    {
      FriendNode *tmp = node;
      node = node->next;
      free(tmp);
    }
    node = node2;
  }

  return -1;
}

/**
 * TODO: Complete this function
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
  int A = get_brand_index(brandNameA);
  int B = get_brand_index(brandNameB);
  if(A != -1 && B != -1)
  {
    brand_adjacency_matrix[A][B] = 1;
    brand_adjacency_matrix[B][A] = 1;
  } 
}

/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */
User *get_suggested_friend(User *user)
{
  User *fr = NULL;
  int highest_mutual = 0;

  for(FriendNode *p = allUsers; p != NULL; p = p->next)
  {
    User *q = p->user;

    if(q == user || in_friend_list(user->friends, q))
    {
      continue;
    }

    int brands_mutual = 0;
    for(BrandNode *node1 = user->brands; node1 != NULL; node1 = node1->next)
    {
      for(BrandNode *node2 = q->brands; node2 != NULL; node2 = node2->next)
      {
        if(strcmp(node1->brand_name, node2->brand_name) == 0)
        {
          brands_mutual++;
        }
      }
    }

    if(brands_mutual > highest_mutual || brands_mutual == highest_mutual && fr == NULL || strcmp(q->name, fr->name) > 0)
    {
      highest_mutual = brands_mutual;
      fr = q;
    }
  }

  return fr;
}

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{
  int add = 0;
  for(int i = 0; i < n; i++)
  {
    User *fr = get_suggested_friend(user);

    if(fr == NULL)
    {
      break;
    }

    if(add_friend(user, fr) == 0)
    {
      add++;
    }
  }

  return add;
}

/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */
int follow_suggested_brands(User *user, int n)
{
  char *brand_can[MAT_SIZE];
  int count = 0;
  int score[MAT_SIZE];
  for(int i = 0; i<MAT_SIZE; i++)
    score[i] = 0;

  for(int i = 0; i < MAT_SIZE; i++)
  {
    if(in_brand_list(user->brands, brand_names[i]) == false)
    {
      int p = 0;
      for(BrandNode *br = user->brands; br != NULL; br = br->next)
      {
        int user_index = get_brand_index(br->brand_name);
        int name_index = get_brand_index(brand_names[i]);
        if(brand_adjacency_matrix[user_index][name_index] == 1)
        {
          p++;
        }
      }
      score[count] = p;
      brand_can[count] = brand_names[i];
      count++;
    }
  }

  for(int i = 0; i < count - 1; i++)
  {
    for(int j = i + 1; j < count; j++)
    {
      if(score[i] < score[j] || score[i] == score[j] && strcmp(brand_can[i], brand_can[j]) < 0)
      {
        int tmp = score[i];
        score[i] = score[j];
        score[j] = tmp;

        char *tmp_brand = brand_can[i];
        brand_can[i] = brand_can[j];
        brand_can[j] = tmp_brand;
      }
    }
  }

  int follow = 0;
  for(int i = 0; i < n && i < count; i++)
  {
    user->brands = insert_into_brand_list(user->brands, brand_can[i]);
    follow++;
  }
  return follow;
}


