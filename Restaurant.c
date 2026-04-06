#include <stdio.h>

int main()
{
    int tables[30] = {0};
    int tableNo;

    int choice, qty;
    float total, itemTotal;
    char newOrder;

    char items[10][30] = {
        "Burger","Pizza","Momo","Sandwich","Chowmein",
        "Fried Rice","Chicken Curry","Coffee","Tea","Cold Drink"
    };

    float price[10] = {120,250,150,100,180,200,300,90,60,80};

    FILE *fp;
    fp = fopen("order.txt","a");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    printf("=========== RESTAURANT ORDER SYSTEM ===========\n");

    do
    {
        total = 0;   // reset total for new customer

        /* TABLE SELECTION */
        while(1)
        {
            printf("Enter Table Number (1-30): ");
            scanf("%d",&tableNo);

            if(tableNo < 1 || tableNo > 30)
            {
                printf("Invalid table number! Try again.\n");
            }
            else if(tables[tableNo-1] == 1)
            {
                printf("Table %d is already booked! Enter another table number.\n", tableNo);
            }
            else
            {
                tables[tableNo-1] = 1;
                break;
            }
        }

        fprintf(fp,"\n====== TABLE %d ======\n",tableNo);

        /* DISPLAY MENU */
        printf("\n----------- MENU -----------\n");
        for(int i=0;i<10;i++)
        {
            printf("%d. %-15s Rs %.2f\n",i+1,items[i],price[i]);
        }

        /* MULTIPLE ITEM ORDER AT ONCE */
        int n;
        printf("\nHow many different items do you want to order? ");
        scanf("%d",&n);

        for(int i=0; i<n; i++)
        {
            printf("\nEnter item number (1-10): ");
            scanf("%d",&choice);

            if(choice < 1 || choice > 10)
            {
                printf("Invalid choice! Try again.\n");
                i--;   // retry same iteration
                continue;
            }

            printf("Enter quantity: ");
            scanf("%d",&qty);

            itemTotal = price[choice-1] * qty;
            total += itemTotal;

            printf("Added: %s x %d = Rs %.2f\n",
                   items[choice-1], qty, itemTotal);

            fprintf(fp,"%s x %d = Rs %.2f\n",
                    items[choice-1], qty, itemTotal);
        }

        /* BILL */
        printf("\n=========== BILL ===========\n");
        printf("Table Number : %d\n",tableNo);
        printf("Total Amount : Rs %.2f\n",total);
        printf("============================\n");

        fprintf(fp,"Total Bill : Rs %.2f\n",total);
        fprintf(fp,"===========================\n");

        /* NEW CUSTOMER */
        printf("\nTake another order? (y/n): ");
        scanf(" %c",&newOrder);

    } while(newOrder=='y' || newOrder=='Y');

    fclose(fp);

    printf("Order saved successfully!\n");

    return 0;
}