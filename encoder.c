#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **citire(int *size2, int *n)
{   //citesc si aloc memorie pe parcurs
	int i;
	int size = (int)*size2;
	int conditie = 1; // cat e posibila citirea
	char **array;
	array = (char **)calloc(1, sizeof(char *));
	char *linie = (char *)calloc(60, sizeof(linie));
	while (conditie) {
		array = (char **)realloc(array, (size + 1) * sizeof(char *));
		array[size] = (char *)calloc(1000, sizeof(char));
		fgets(linie, 60, stdin); //citesc un string
		if (strcmp("END\n", linie) != 0) { // verific daca am ajuns la END cumva
			strcpy(array[size], linie); //construiesc array
			size++;
		} else
			conditie = 0;
			//am ajuns la END
	}
	*n = atoi(array[size - 1]); // convertesc n(char->int); 
								// am nevoie de el
	*size2 = size - 1;
	return array;
}

int ce_tip_e(char *un_string)
{
	// intoarce 1 pt cuvinte
	// 2 pt caractere, 3 pt numere
	int i;
	for (i = 0; i < strlen(un_string); i++) {
		if ((i == 0 && un_string[i] == '-') || isdigit(un_string[i])) ;
		else
			break;
	} // verific in ce categorie se afla inputul
	if (i == strlen(un_string) - 1
	    && (!(strlen(un_string) == 2 && un_string[0] == '-')))
		return 3;
	if (strlen(un_string) == 2)	// pentru ca \n incurca
		return 2;
	return 1;
}

void cuv_carac_nr(char **array, int *size)
{
	// intoarce 1 pt cuv, 2 pt caract, 3 pt nr
	int i, j, conditie;
	int lungime;
	int numar = 0;
	int carac = 0;
	int cuv = 0;
	// am nevoie de contori
	for (i = 0; i < *size; i++) {
		if (ce_tip_e(array[i]) == 3) {
			numar++;
		}
		if (ce_tip_e(array[i]) == 2)
			carac++;
		if (ce_tip_e(array[i]) == 1)
			cuv++;
	}
	printf("%d %d %d", cuv, carac, numar);

}

int codif_nr_ret_int(char *input)
{ 
	int n, i, j;
	int local, max = 0, ch, min;
	int conditie = 0;
	int conditie2;
	int local2;
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
	n = strlen(input);
	conditie = 1;
	if (conditie == 1) {
		if (input[0] == '-') {
			conditie2 = 0;	// adica e negativ
			ch = atoi(input);
			// convertesc din char in int;
			min = ch * (-1);
			// folosesc forma lui pozitiva pentru a modifica
			for (i = 1; i < n; i++) { // obtin numere prin rotatie
				input[n] = input[1];

				for (j = 1; j < n; j++) {
					input[j] = input[j + 1];
				}
				input[n] = '\0';
				local = atoi(input);
				local2 = local * (-1); // iau inputul initial drept pivot

				if (local2 < min)
					min = local2; // pentru negative am nevoie de mini
			}
			return min;

		}
		else {
			conditie2 = 1; // adica e pozitiv
			ch = atoi(input); // convertesc iar
			for (i = 0; i < n; i++) {
				input[n] = input[0];

				for (j = 0; j < n; j++) {
					input[j] = input[j + 1];
				}
				input[n] = '\0';
				local = atoi(input); // drept pivot
				if (local > max)
					max = local;
			}
			return max;

		}

	}
}

int contains_digit(char *termen)
{
	int i; // verific daca exista vreo cifra
	for (i = 0; i < strlen(termen); i++) {
		if (isdigit(termen[i]))
			return 1;
	}
	return 0;
}

void swap(char *a, char *b)
{ // interschimb valorile
	char aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void reverse_string(char *string)
{ // intorc stringul; am nevoie de forma in ordine inversa
	int i;
	for (i = 0; i < strlen(string) / 2; i++)
		swap(&(string[i]), &(string[strlen(string) - 1 - i]));
}

char *termen_nou(char *termen)
{
	if (termen[strlen(termen) - 1] == '\n')
		termen[strlen(termen) - 1] = '\0';
	int lungime;
	lungime = strlen(termen); // lungimea stringului
	int i, j, l, c, n, d;
	int div;
	for (i = (lungime / 2); i >= 1; i--) {
		if (lungime % i == 0) { // aflu divizorul maxim
			div = i;
			break;
		}
	} // incep sa modific forma 
	if (termen[strlen(termen) - 1] == '\n')
		termen[strlen(termen)] = '\0';

	if (contains_digit(termen)) {
		reverse_string(&(termen[div]));
		strncpy(&(termen[strlen(termen)]), termen, div);
		termen = &(termen[div]); // daca are cifra
	} else { // daca n-are cifra 
		// ex: termen = carte => div = 1
		strncpy(&(termen[strlen(termen)]), termen, div);
		// ex: termen = cartec
		termen = &(termen[div]);
		// ex: termen = artec
	}
	return termen;
}

int number_of_occurrences(char c, char **array, int i)
{ // calculez de cate ori apare in string
	int j, k;
	int de_cate_ori_apare = 0;
	for (j = 0; j < i; j++) {
		for (k = 0; k < strlen(array[j]); k++)
			if (array[j][k] == c)
				de_cate_ori_apare++;
	}
	return de_cate_ori_apare;
}

char *codifica_caracter(char **array, int i, char *line)
{
	// fac overwrite \n cu \0
	if (i == 0) {
		array[i][1] = '\0';
		return array[i];
	}
	line[1] = '\0';
	int j, k;
	int aux;
	char cel_mai_des = '_';
	char cel_mai_rar = '?';
	int nr_aparitii_cel_mai_des = 0;
	int nr_aparitii_cel_mai_rar = 1000000;
	for (j = 0; j < i; j++) {
		// pentru fiecare string anterior
		for (k = 0; k < strlen(array[j]); k++) {
			// pentru fiecare caracter din acel string
			aux = number_of_occurrences(array[j][k], array, i);
			if (aux > nr_aparitii_cel_mai_des) {
				cel_mai_des = array[j][k];
				nr_aparitii_cel_mai_des = aux;
			}
			if (aux < nr_aparitii_cel_mai_rar) {
				cel_mai_rar = array[j][k];
				nr_aparitii_cel_mai_rar = aux;
			}
		}
	}
	array[i][1] = array[i][0];
	//am mutat caracterul introdus de la tastatura
	// pe pozitia a2-a
	array[i][0] = cel_mai_des;
	array[i][2] = cel_mai_rar;
	array[i][3] = '\0';
	return array[i];
}

char **codifica_array(char **array, int size)
{
	int i;
	int nr_codificat;
	//char *nr_codificat_as_string;
	for (i = 0; i < size; i++) {
		if (ce_tip_e(array[i]) == 3) {
			nr_codificat = codif_nr_ret_int(array[i]);
			sprintf(array[i], "%d", nr_codificat);
			continue;
		}
		if (ce_tip_e(array[i]) == 1) {
			array[i] = termen_nou(array[i]);
			continue;
			//imi ntra pe amandoua ramurile
		}
		if (ce_tip_e(array[i]) == 2) {
			array[i] = codifica_caracter(array, i, array[i]);
			continue; // ca sa nu mai intre pe ambele ramuri
		}
	}
	return array;
}

typedef struct {
	char *c;
	double complexitate;
} bucata;

bucata *calc_complex(bucata * bucati, int nr_bucati)
{ // am nevoie de complexitate 
	int i, j;
	double suma;
	for (i = 0; i < nr_bucati; i++) {
		suma = 0;
		for (j = 0; j < strlen(bucati[i].c); j++) {
			suma += bucati[i].c[j];
		}
		bucati[i].complexitate = suma / strlen(bucati[i].c);
	}
	return bucati;
}

bucata *imparte_in_bucati(bucata * bucati, char *s, int size, int n,
			  int *nr_bucati)
{   // folosesc n-ul introdus de la tastatura
	// ca sa impart in bucati / partitii
	int lungime_string = strlen(s);
	int lungime_bucata = lungime_string / n;
	bucati = (bucata *) malloc(5000 * sizeof(bucata));
	int i;
	for (i = 0;; i++) {
		// i parcurge vectorul bucati
		(*nr_bucati)++;
		bucati[i].c = (char *)malloc(sizeof(lungime_bucata));
		strncpy(bucati[i].c, &(s[i * lungime_bucata]), lungime_bucata);
		// pentru "conversia" tip in tip* folosesc & (dereferentiere)
		// pentru "conversia" tip* in tip folosesc *
		if ((i + 2) * lungime_bucata > strlen(s)) {
			bucati[i].c =
			    strcpy(bucati[i].c, &(s[i * lungime_bucata]));
			break;
		}
		bucati[i].c[lungime_bucata] = '\0';
	}
	bucati = calc_complex(bucati, *nr_bucati);
	return bucati;
}

void mergeSort(bucata * bucati, int n)
{ // acum sortez
	int i, j;
	bucata aux;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++) {
			if (bucati[i].complexitate < bucati[j].complexitate) {
				aux = bucati[i];
				bucati[i] = bucati[j];
				bucati[j] = aux;
			}
			if (bucati[i].complexitate == bucati[j].complexitate) {
				if (strcmp(bucati[i].c, bucati[j].c) < 0) {
					aux = bucati[i];
					bucati[i] = bucati[j];
					bucati[j] = aux;
				}
			}
		}
}

int main()
{
	int i;
	char *s = (char *)malloc(5000 * sizeof(char));
	char *q = (char *)malloc(5000 * sizeof(char));
	s[0] = '\0';
	q[0] = '\0';
	char *r = (char *)malloc(5000 * sizeof(char));
	char *p = (char *)malloc(5000 * sizeof(char));
	char *w = (char *)malloc(5000 * sizeof(char));
	r[0] = '\0';
	p[0] = '\0';
	int size = 0;
	int n;
	char **array = citire(&size, &n);
	cuv_carac_nr(array, &size);
	array = codifica_array(array, size);
	// imi codifica matricea de stringuri de la intrare
	printf("\n");
	for (i = 0; i < size; i++) {
		sprintf(q, "%s", array[i]);
		s = strcat(s, q);
	}
	puts(s);
	bucata *bucati = NULL;
	int nr_bucati = 0;
	bucati = imparte_in_bucati(bucati, s, size, n, &nr_bucati);
	mergeSort(bucati, n);

	for (i = 0; i < n; i++) {
		if (i > n / 2) {
			break;
		}
		if (i != 0) {
			sprintf(w, "%s", bucati[n - i].c);
			p = strcat(p, w);
		}

		sprintf(r, "%s", bucati[i].c);
		if (strcmp(r, w))
			p = strcat(p, r);
	}
	puts(p);

	return 0;
}
