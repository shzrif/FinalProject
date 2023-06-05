#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char nama[100];
    char penyakit[100];
    struct node* next;
};

struct queue {
    struct node* head, * ujung;
};

void enqueue(struct queue* q) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    printf("\nMasukkan Nama pasien: ");
    scanf("%*c");
    fgets(temp->nama, sizeof(temp->nama), stdin);
    printf("Diagnosa: ");
    fgets(temp->penyakit, sizeof(temp->penyakit), stdin);
    temp->nama[strcspn(temp->nama, "\n")] = '\0';
    temp->penyakit[strcspn(temp->penyakit, "\n")] = '\0';
    temp->next = NULL;

    if (q->ujung == NULL) {
        q->head = q->ujung = temp;
    }
    else {
        q->ujung->next = temp;
        q->ujung = temp;
    }

    FILE* ptr = fopen("Report.txt", "a");
    if (ptr == NULL) {
        printf("Terjadi masalah pada file\n");
        return;
    }

    fprintf(ptr, "Nama Pasien: %s\nDiagnosa: %s\n\n", temp->nama, temp->penyakit);
    fclose(ptr);
}

void dequeue(struct queue* q) {
    if (q->head == NULL) {
        printf("\nTidak ada data pasien yang dimasukkan");
        return;
    }
    printf("\nPasien dengan nama '%s' telah memasuki ruangan dan dihapus dari waiting list\n", q->head->nama);
    struct node* temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL)
        q->ujung = NULL;
    free(temp);
}

void display(struct queue* q) {
    if (q->head == NULL) {
        printf("Data masih kosong! Silahkan mendaftarkan diri terlebih dahulu.\n");
        return;
    }
    printf("\n==================Waiting list==================");
    struct node* temp = q->head;
    while (temp != NULL) {
        printf("\nNama Pasien: %s\nDiagnosa: %s\n", temp->nama, temp->penyakit);
        temp = temp->next;
    }
}

void abjad(struct queue* q) {
    if (q->head == NULL) {
        printf("Data masih kosong! Silahkan mendaftarkan diri terlebih dahulu.\n");
        return;
    }
    struct node* current = q->head;
    struct node* sorted = NULL;

    while (current != NULL) {
        struct node* next = current->next;

        if (sorted == NULL || strcmp(current->nama, sorted->nama) < 0) {
            current->next = sorted;
            sorted = current;
        }
        else {
            struct node* temp = sorted;
            while (temp->next != NULL && strcmp(current->nama, temp->next->nama) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    printf("==================Waiting list==================\n");
    struct node* temp = sorted;
    while (temp != NULL) {
        printf("Nama Pasien: %s\nDiagnosa: %s\n\n", temp->nama, temp->penyakit);
        temp = temp->next;
    }

    // Free the memory of the sorted list
    while (sorted != NULL) {
        struct node* temp = sorted;
        sorted = sorted->next;
        free(temp);
    }
}

int main() {
	int input,dis;
    struct queue q;
    q.head = q.ujung = NULL;
    FILE* ptr;
    ptr = fopen("Report.txt", "w");
    fprintf(ptr, "==================Waiting list==================\n");
    fclose(ptr);

    while (input != 4) {
        printf("======================================\n"
               "|                                    |\n"
               "|     	Data pengunjung klinik       |\n"
               "|                                    |\n"
               "======================================\n"
               "======================================\n"
               "|            Menu Utama:             |\n"
               "|                                    |\n"
               "|  1. Pendaftaran Pasien             |\n"
               "|  2. Pemanggilan Pasien             |\n"
               "|  3. Waiting list                   |\n"
               "|  4. Tutup Klinik                   |\n"
               "======================================\n");
        printf("Pilihlah opsi yang ingin dijalankan: ");
        scanf("%d", &input);
        if (input == 1) {
            system("cls");
            enqueue(&q);
            system("pause");
            system("cls");
        }
        else if (input == 2) {
            system("cls");
            dequeue(&q);
            system("pause");
            system("cls");
        }
        else if (input == 3) {
            system("cls");
            printf("1. Waktu input\n2. Abjad\ndata ingin ditampilkan secara : ");
            scanf("%d",&dis);
            if (dis == 1){
            system("cls");
            display(&q);
            printf("\n");	
			}
			if(dis == 2){
			system("cls");
			abjad(&q);
			printf("\n");
			}
            system("pause");
            system("cls");
        }
        else if (input == 4) {
            break;
        }
        else {
            printf("Pilihan salah, harap pilih kembali\n");
            system("pause");
            system("cls");
        }
    }
	system("cls");
    ptr = fopen("Report.txt", "a");
    if (ptr == NULL) {
        printf("Terjadi masalah pada file\n");
        return 1;
    }
}
