#include "functions.h"
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

// logic ham

int count = 0;         
Category list[100];
int productCount = 0;
Product menu[100]; 
 
// ham back va thoat chuong trinh 
void backandexit() {
    char input;
    while (1) {
        printf("Go back (B) or Exit (0): ");
        input = getchar();
        getchar();
        fflush(stdin); 
        if (input == 'b' || input == 'B') {
            printf("Quay lai chuong trinh.\n");
            system("cls");
            return; 
        } else if (input == '0') {
            printf("Thoat chuong trinh. Tam biet!\n");
            exit(0); 
        }
    }
}
 
// ham hien thi danh sach danh muc 
void showCategories(){
    if (count == 0) {
        printf("Danh muc chua duoc them!\n");
        return; 
    } else {
        printf("****** CATEGORY LIST ******\n");
	    printf("+-------+---------------------------+\n");
	    printf("| %-5s | %-25s |\n", "ID", "Ten danh muc"); 
	    printf("+-------+---------------------------+\n");
	    for (i = 0; i < count; i++) {
	        printf("| %-5d | %-25s |\n", list[i].id, list[i].name); 
	    }
	    printf("+-------+---------------------------+\n");
    }
}

// ham them danh muc vao danh sach
void addCategory() {
    if (count >= 100) {
        return; 
    }
    Category newCategory;
    int i, inserted = 0;
    for (i = 0; i < count; i++) {
        if (list[i].id == 0) {
            newCategory.id = i + 1;
            inserted = 1;
            break;
        }
    }
    if (!inserted) {
        newCategory.id = count + 1;
    }
    while (1) {
        printf("Nhap ten danh muc can them: ");
        fgets(newCategory.name, sizeof(newCategory.name), stdin);
        newCategory.name[strcspn(newCategory.name, "\n")] = '\0';
        if (strlen(newCategory.name) == 0) {
            printf("Ten danh muc khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        int idDuplicate = 0;
        for (i = 0; i < count; i++) {
            if (strcmp(list[i].name, newCategory.name) == 0) {
                idDuplicate = 1;
                break;
            }
        }
        if (idDuplicate) {
            printf("Ten danh muc da ton tai! Vui long nhap ten khac.\n");
        } else {
            list[count] = newCategory;
            count++;
            printf("Danh muc da duoc them!\n");
            saveCategoriesToFile();
            break;
        }
    }
}


// sua danh muc trong danh sach
void editCategory() {
	showCategories();
    int idToEdit, found = 0; 
    printf("Nhap ID danh muc muon sua: ");
    scanf("%d", &idToEdit);
    getchar();
    fflush(stdin); 
    for ( i = 0; i < count; i++) { 
        if (list[i].id == idToEdit) {
            found = 1;  
            while (1) {
                printf("Nhap ten danh muc moi: ");
                fgets(list[i].name, sizeof(list[i].name), stdin);
                list[i].name[strcspn(list[i].name, "\n")] = '\0';  
                if (strlen(list[i].name) == 0) {
                    printf("Ten danh muc khong duoc de trong! Vui long nhap lai.\n");
                    continue;  
                }
                int check = 0; 
                for ( j = 0; j < count; j++) { 
                    if (i != j && strcmp(list[j].name, list[i].name) == 0) {
                        check = 1;
                        break;
                    }
                }
                if (check) {
                    printf("Ten danh muc da ton tai! Vui long nhap ten khac.\n");
                } else {
                    printf("Danh muc da duoc sua thanh cong!\n");
                    saveCategoriesToFile();
                    break; 
                }
            }
            break;
        }
    }

    if (!found) {
        printf("ID danh muc khong ton tai!\n");
    }
}


// xoa danh muc trong danh sach
void deleteCategory() {
	showCategories();
    int idToDelete, found = 0; 
    printf("Nhap ID danh muc muon xoa: ");
    scanf("%d", &idToDelete);
    getchar(); 
    if (idToDelete <= 0 || idToDelete > count) {
        printf("ID danh muc khong ton tai!\n");
        return;
    }
    for ( i = 0; i < count; i++) { 
        if (list[i].id == idToDelete) {
            found = 1;
            printf("Day co phai danh muc ban muon xoa khong?\n");
            printf("+-------+---------------------------+\n");
            printf("| %-5s | %-25s |\n", "ID", "Ten danh muc"); 
            printf("+-------+---------------------------+\n");
            printf("| %-5d | %-25s |\n", list[i].id, list[i].name);
            printf("+-------+---------------------------+\n");
            char reply[10]; 
            while (1) {
                printf("Ban co chac chan muon xoa danh muc nay? (Y/N): ");
                fgets(reply, sizeof(reply), stdin); 
                reply[strcspn(reply, "\n")] = '\0'; 
                if (strcmp(reply, "Y") == 0 || strcmp(reply, "y") == 0) {
                    for (j = i; j < count - 1; j++) {
                        list[j] = list[j + 1];  
                    }
                    memset(&list[count - 1], 0, sizeof(Category));  
					int k; 
                    for ( k = 0; k < count - 1; k++) {
                        list[k].id = k + 1; 
                    }
                    count--; 
                    printf("Danh muc da duoc xoa thanh cong!\n");
                    saveCategoriesToFile();
                    break;
                } else if (strcmp(reply, "N") == 0 || strcmp(reply, "n") == 0) {
                    printf("Da huy thao tac xoa danh muc.\n");
                    break;
                } else {
                    printf("Lua chon khong hop le! Vui long nhap lai (Y/N).\n");
                }
            }
            break;
        }
    }
    if (!found) {
        printf("ID danh muc khong ton tai!\n"); 
    }
}


// ham tim kiem danh muc 
void searchCategory() {
    char search[20];
    int found = 0;
    printf("Nhap ten danh muc muon tim kiem: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0'; 
    strlwr(search);
    printf("\nKet qua tim kiem danh muc: \"%s\"\n", search);
    for ( i = 0; i < count; i++) {
        if (strstr(list[i].name, search) != NULL) {
            if (!found) { 
                printf("+-------+---------------------------+\n");
                printf("| %-5s | %-25s |\n", "ID", "Ten danh muc");
                printf("+-------+---------------------------+\n");
            }
            printf("| %-5d | %-25s |\n", list[i].id, list[i].name);
            found = 1;
        }
    }
    if (!found) { 
        printf("Khong tim thay danh muc nao phu hop!\n");
    } else {
        printf("+-------+---------------------------+\n");
    }
}


void sortCategory() {
    int choice, i, j;
    Category temp;
    printf("Chon thu tu sap xep danh muc theo ten:\n");
    printf("1. Sap xep theo ten (A-Z)\n");
    printf("2. Sap xep theo ten (Z-A)\n");
    printf("Nhap lua chon (1/2): ");
    scanf("%d", &choice);
    getchar(); 
    if (choice != 1 && choice != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            int compare = strcmp(list[i].name, list[j].name);
            if ((choice == 1 && compare > 0) || (choice == 2 && compare < 0)) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    printf("\nDanh sach danh muc sau khi sap xep:\n");
    printf("+-------+---------------------------+\n");
    printf("| %-5s | %-25s |\n", "ID", "Ten danh muc");
    printf("+-------+---------------------------+\n");
    for (i = 0; i < count; i++) {
        printf("| %-5d | %-25s |\n", list[i].id, list[i].name);
    }
    printf("+-------+---------------------------+\n");
}

void saveCategoriesToFile() {
    FILE *file = fopen("categories.dat", "wb");
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file); 
    fwrite(list, sizeof(Category), count, file);
    fclose(file);
    printf("Danh muc da duoc luu vao file.\n");
}

void loadCategoriesFromFile() {
    FILE *file = fopen("categories.dat", "rb");
    if (file == NULL) {
        printf("Chua co du lieu danh muc trong file.\n");
        return;
    }
    fread(&count, sizeof(int), 1, file); 
    fread(list, sizeof(Category), count, file); 
    fclose(file);
}
 
 
void printlogin(){   
// hien thi man hinh dang nhap  
	int choice; 
	char password[50];
	const char pass[]= "123";
	while(1){
	printf("****** STORE MANAGEMENT ****** \n");
	printf("\n");
	printf("\t    LOGIC \n");
	printf("==============================\n"); 
	printf("Email: AdminStore@gmail.com\n");
	printf("Password: ");
	scanf("%s", &password);
	if (strcmp(pass, password) == 0) {
            printf("Dang nhap thanh cong.\n \n \n");
			break;
        } else {
            printf("Sai password! Vui long nhap lai.\n \n \n");
        }
    }
    system("cls"); 
	while(1){
		printf("****** STORE MANAGEMENT ****** \n");
		printf("\n");
		printf("      CHOOSE YOUR CHOICE \n");
		printf("================================\n"); 
		printf("[1]. CATEGORY\n");
		printf("[2]. PRODUCTS\n");
		printf("[3]. EXIT PROGRAM\n");
		printf("================================\n"); 
		printf("Nhap lua chon cua ban: ");
		if (scanf("%d", &choice) != 1) {  
	        printf("Lua chon khong hop le.\n\n");
	        while (getchar() != '\n');
	        continue; 
	    }
		switch (choice){
			case 1:{
				system("cls"); 
				int choicecategory;
				while(1){
					printf("\n********* MENU CATEGORY *********\n");
					printf("================================\n"); 
	                printf("[1]. Show CATEGORY\n");
	                printf("[2]. Add CATEGORY\n");
	                printf("[3]. Edit CATEGORY\n");
	                printf("[4]. Delete CATEGORY\n");
	                printf("[5]. Search CATEGORY\n");
	                printf("[6]. Sort CATEGORY\n");
	                printf("[7]. Exit Menu CATEGORY\n");
					printf("================================\n"); 
	                printf("Nhap lua chon cua ban: ");
	                scanf("%d", &choicecategory);
	                getchar(); 
	                fflush(stdin); 
	                switch (choicecategory){
	                	case 1:{
	                		system("cls"); 
	                		// hien thi cac danh muc 
	                		showCategories();
	                		backandexit();
                            break;
						} 
						case 2:{
							system("cls"); 
							// them danh muc  
							addCategory();
							backandexit();
							break;
						} 
						case 3:{
							// sua danh muc 
							system("cls");
							editCategory(); 
							backandexit();
							break;
						} 
						case 4:{
							// xoa danh muc  
							system("cls");
							deleteCategory();
							fflush(stdin); 
							backandexit();
							break;
						} 
						case 5:{
							// tim kiem danh muc 
							system("cls");
							searchCategory();
							backandexit();
							break;
						} 
						case 6:{
							// sap xep danh muc
							system("cls"); 
							sortCategory();
							backandexit(); 
							break;
						} 
						case 7:
							system("cls");
							printf("\n"); 
							printf("\t   EXIT MENU CATEGORY\n"); 
							printf("============== Thank You ==============\n");
							printf("============= See You Soon ============\n");
							printf("\n"); 
                            goto exit; 
                        default:
                            printf("Lua chon khong hop le \n");
                    }
                }
                exit:
                break;
            }
			case 2:{
				// in cac san pham hien co 
				system("cls"); 
				int choiceproducts;
				while(1){
					printf("\n********* MENU PRODUCTS *********\n");
					printf("================================\n"); 
	                printf("[1]. Show PRODUCTS\n");
	                printf("[2]. Add PRODUCTS\n");
	                printf("[3]. Edit PRODUCTS\n");
	                printf("[4]. Delete PRODUCTS\n");
	                printf("[5]. Search PRODUCTS\n");
	                printf("[6]. Sort PRODUCTS\n");
	                printf("[7]. Filter PRODUCTS\n");
	                printf("[8]. Exit Menu PRODUCTS\n");
					printf("================================\n"); 
	                printf("Nhap lua chon cua ban: ");
	                scanf("%d", &choiceproducts);
	                getchar(); 
	                fflush(stdin); 
	                switch (choiceproducts){
	                	case 1:{
	                		system("cls"); 
	                		// hien thi cac san pham 
	                		showProduct();
	                		backandexit();
                            break;
						} 
						case 2:{
							system("cls"); 
							// them san pham  
							addProduct();
							backandexit();
							break;
						} 
						case 3:{
							// sua san pham 
							system("cls");
							editProduct(); 
							backandexit();
							break;
						} 
						case 4:{
							// xoa san pham 
							system("cls");
							deleteProduct();
							backandexit();
							break;
						} 
						case 5:{
							// tim kiem san pham 
							system("cls");
							searchProduct();
							backandexit();
							break;
						} 
						case 6:{
							// sap xep san pham 
							system("cls"); 
							sortProduct();
							backandexit();
							break;
						} 
						case 7:{
							// loc san pham 
							system("cls"); 
							filterProduct();
							fflush(stdin); 
							backandexit();
							break;
						} 
						case 8:
							system("cls");
							printf("\n"); 
							printf("\t   EXIT MENU PRODUCTS\n"); 
							printf("============== Thank You ==============\n");
							printf("============= See You Soon ============\n");
							printf("\n"); 
                            goto exitProducts; 
                        default:
                            printf("Lua chon khong hop le \n");
                    }
                }
                exitProducts:
                break;
            }
			case 3:{
				printf("\t     EXIT PROGRAM\n"); 
				printf("============== Thank You ==============\n");
				printf("============= See You Soon ============\n");
				return ; 
				break;
			} 
			default:
				printf("Lua chon khong hop le \n");
				printf("\n");
		} 
    }
}

// in cac san san pham
void showProduct() {
    if (productCount == 0) {
        printf("Chua co san pham nao.\n");
        return;
    }
    printf("===========================================================================================\n");
    printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
    printf("===========================================================================================\n");
    for (i = 0; i < productCount; i++) {
        printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
    }
    printf("===========================================================================================\n");
}

// them san pham 
void addProduct() {
    showCategories();
    int categoryId;
    printf("Nhap ID danh muc de them san pham: ");
    scanf("%d", &categoryId);
    getchar(); 
    int categoryExists = 0;
    for ( i = 0; i < count; i++) {
        if (list[i].id == categoryId) {
            categoryExists = 1;
            break;
        }
    }
    if (!categoryExists) {
        printf("ID danh muc khong ton tai.\n");
        fflush(stdin); 
		return;
    }
    Product p;
    p.id = productCount + 1; 
    while (1) {
        printf("Nhap ten san pham: ");
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';
        if (strlen(p.name) == 0) {
            printf("Ten san pham khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }
        int nameDuplicate = 0;
        for (i = 0; i < productCount; i++) {
            if (strcmp(menu[i].name, p.name) == 0) {
                nameDuplicate = 1;
                break;
            }
        }
        if (nameDuplicate) {
            printf("Ten san pham da ton tai! Vui long nhap ten khac.\n");
        } else {
            break;
        }
    }
    strcpy(p.categoryname, list[categoryId - 1].name);
    while(1){
	    printf("Nhap gia tien: ");
		scanf("%f", &p.price);
		if(p.price < 1){
	        printf("Gia khong hop le.\n");
	        fflush(stdin);
	        return;
		}
		break;
	}
	fflush(stdin); 
	while (1){
	    printf("Nhap so luong: ");
	    scanf("%d", &p.quantity);
	    if(p.quantity < 1){
		    printf("So luong khong hop le.\n");
		    fflush(stdin);
		    return;
			}
			break;
		}
    menu[productCount] = p;
    productCount++;
    printf("San pham da duoc them thanh cong!\n");
    saveProductsToFile();
    fflush(stdin); 
}

void editProduct() {
    showProduct(); 
    int productedit;
    printf("Nhap ID san pham muon sua: ");
    scanf("%d", &productedit);
    getchar(); 
    int productExists = 0;
    int productIndex = -1;
    for ( i = 0; i < productCount; i++) {
        if (menu[i].id == productedit) {
            productExists = 1;
            productIndex = i;
            break;
        }
    }
    if (!productExists) {
        printf("ID san pham khong ton tai.\n");
        return;
    }
    printf("Thong tin san pham hien tai:\n");
    printf("===========================================================================================\n");
    printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
    printf("===========================================================================================\n");
	printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[productIndex].id, menu[productIndex].name, menu[productIndex].price, menu[productIndex].quantity, menu[productIndex].categoryname);
    printf("===========================================================================================\n");
    printf("Nhap ten san pham moi: ");
    fgets(menu[productIndex].name, sizeof(menu[productIndex].name), stdin);
    menu[productIndex].name[strcspn(menu[productIndex].name, "\n")] = '\0'; 
	printf("Nhap gia moi: ");
	scanf("%f", &menu[productIndex].price);
    fflush(stdin); 
	printf("Nhap so luong moi: ");
	scanf("%d", &menu[productIndex].quantity);
    getchar(); 
    char newCategory[50];
    int categoryValid = 0;
    do {
        printf("Nhap danh muc moi: ");
        fgets(newCategory, sizeof(newCategory), stdin);
        newCategory[strcspn(newCategory, "\n")] = '\0'; 
        for ( i = 0; i < count; i++) {
            if (strcmp(list[i].name, newCategory) == 0) {
                categoryValid = 1;
                break;
            }
        }
        if (!categoryValid) {
            printf("Danh muc '%s' khong ton tai. Vui long nhap lai.\n", newCategory);
        }
    } while (!categoryValid);
    strcpy(menu[productIndex].categoryname, newCategory); 
    printf("Thong tin san pham da duoc cap nhat thanh cong.\n");
    saveProductsToFile();
}

void deleteProduct() {
	showProduct(); 
    int idToDelete, found = 0;
    printf("Nhap ID san pham muon xoa: ");
    scanf("%d", &idToDelete);
    getchar(); 
    if (idToDelete <= 0 || idToDelete > productCount) {
        printf("ID san pham khong ton tai!\n");
        return;
    }
    for (i = 0; i < productCount; i++) {
        if (menu[i].id == idToDelete) {
            found = 1;
		    printf("===========================================================================================\n");
		    printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
		    printf("===========================================================================================\n");
            printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
            printf("===========================================================================================\n");
            char reply[10];
            while (1) {
                printf("Ban co chac chan muon xoa san pham nay? (Y/N): ");
                fgets(reply, sizeof(reply), stdin);
                reply[strcspn(reply, "\n")] = '\0';
                if (strcmp(reply, "Y") == 0 || strcmp(reply, "y") == 0) {
                    for (j = i; j < productCount - 1; j++) {
                        menu[j] = menu[j + 1];  
                    }
                    memset(&menu[productCount - 1], 0, sizeof(Product)); 
                    productCount--; 
					int k; 
                    for (k = 0; k < productCount; k++) {
                        menu[k].id = k + 1; 
                    }
                    printf("San pham da duoc xoa thanh cong!\n");
                    saveProductsToFile();
                    break;
                } else if (strcmp(reply, "N") == 0 || strcmp(reply, "n") == 0) {
                    printf("Da huy thao tac xoa san pham.\n");
                    break;
                } else {
                    printf("Lua chon khong hop le! Vui long nhap lai (Y/N).\n");
                }
            }
            break;
        }
    }
    if (!found) {
        printf("ID san pham khong ton tai!\n");
    }
}


void searchProduct() {
    char search[50];
    int found = 0;
    printf("Nhap ten san pham muon tim kiem: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0'; 
    strlwr(search);
    printf("\nKet qua tim kiem san pham la: \n");
    for (i = 0; i < productCount; i++) {
        if (strstr(menu[i].name, search) != NULL) {
            if (!found) {
                printf("===========================================================================================\n");
			    printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
			    printf("===========================================================================================\n");
            }
 	        printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham nao phu hop!\n");
    } else {
       printf("===========================================================================================\n");
    }
}

	
void sortProduct() {
    int choice, i, j;
    Product temp;
    printf("Chon thu tu sap xep san pham theo gia:\n");
    printf("1. Sap xep theo gia (Tang dan)\n");
    printf("2. Sap xep theo gia (Giam dan)\n");
    printf("Nhap lua chon (1/2): ");
    scanf("%d", &choice);
    getchar();
    if (choice != 1 && choice != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    for (i = 0; i < productCount - 1; i++) {
        for (j = i + 1; j < productCount; j++) {
            if ((choice == 1 && menu[i].price > menu[j].price) || 
                (choice == 2 && menu[i].price < menu[j].price)) {
                temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
    printf("\nDanh sach san pham sau khi sap xep:\n");
    printf("===========================================================================================\n");
    printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
    printf("===========================================================================================\n");
    for (i = 0; i < productCount; i++) {
        printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
    }
    printf("===========================================================================================\n");
}

void filterProduct() {
    int choice;
    printf("Chon loai loc san pham:\n");
    printf("1. Loc theo danh muc\n");
    printf("2. Loc theo gia tien\n");
    printf("Nhap lua chon (1/2): ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
        case 1: { 
            int categoryId, found = 0;
            printf("Nhap ID danh muc muon loc: ");
            scanf("%d", &categoryId);
            getchar();
            int categoryExists = 0;
            for ( i = 0; i < count; i++) {
                if (list[i].id == categoryId) {
                    categoryExists = 1;
                    break;
                }
            }
            if (!categoryExists) {
                printf("ID danh muc khong ton tai!\n");
                return;
            }
            printf("San pham trong danh muc da chon la:\n");
            printf("===========================================================================================\n");
            printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
            printf("===========================================================================================\n");
            
            for ( i = 0; i < productCount; i++) {
                if (strcmp(menu[i].categoryname, list[categoryId - 1].name) == 0) {
                     printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
                    found = 1;
                }
            }
            if (!found) {
                printf("Khong co san pham nao trong danh muc nay.\n");
            }
            printf("===========================================================================================\n");
            break;
        }
        case 2: {
            double minPrice, maxPrice;
            printf("Nhap gia tu: ");
            scanf("%lf", &minPrice);
            fflush(stdin);
            if(minPrice < 1){
            	printf("Gia khong hop le.\n");
            	return;
			}
            printf("Nhap gia toi: ");
            scanf("%lf", &maxPrice);
            if(maxPrice < 1){
            	printf("Gia khong hop le.\n");
            	return;
			}
            getchar(); 
            if (minPrice > maxPrice) {
                printf("Khoang gia khong hop le! Gia tu phai nho hon gia toi.\n");
                return;
            }
            printf("San pham trong khoang gia la:\n");
            printf("===========================================================================================\n");
            printf("| %-5s | %-25s | %-10s | %-10s | %-25s |\n", "ID", "Ten", "Gia", "So luong", "Danh muc");
            printf("===========================================================================================\n");
            int found = 0;
            for (i = 0; i < productCount; i++) {
                if (menu[i].price >= minPrice && menu[i].price <= maxPrice) {
                     printf("| %-5d | %-25s | %-10.f | %-10d | %-25s |\n", menu[i].id, menu[i].name, menu[i].price, menu[i].quantity, menu[i].categoryname);
                    found = 1;
                }
            }
            if (!found) {
                printf("Khong co san pham trong khoang gia nay.\n");
            }
            printf("===========================================================================================\n");
            break;
        }
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }
}

void saveProductsToFile() {
    FILE *file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(&productCount, sizeof(int), 1, file);
    for (i = 0; i < productCount; i++) {
        fwrite(&menu[i], sizeof(Product), 1, file);
    }
    fclose(file);
    printf("Danh sach san pham da duoc luu vao file.\n");
}

void loadProductsFromFile() {
    FILE *file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }
    fread(&productCount, sizeof(int), 1, file);
    for ( i = 0; i < productCount; i++) {
        fread(&menu[i], sizeof(Product), 1, file);
    }
    fclose(file);
}

