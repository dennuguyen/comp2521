// COMP2521 20T2 Final Exam Q1
// Read and sort student records

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants

#define MAXNAME 40
#define MAXSTU  20
#define MAXLINE 100

// Student records
typedef struct _stu_rec
{
	int   zid;
	char  name[MAXNAME];
	int   program;
	float wam;
} Student;

// Possible sort fields
typedef enum { BY_ZID, BY_NAME } Ordering;

// Helper functions
int readStudents(FILE *, Student *);
void sortStudents(Student *, int, Ordering);
void showStudents(FILE *, Student *, int);

int main(int argc, char **argv)
{
	Student  students[MAXSTU]; // array of student records
	int      nstudes;          // # records filled in array
	Ordering order = BY_ZID;   // order by zid or name

	// handle optional command-line argument
	// default ordering is by zid
	if (argc > 1 && strcmp(argv[1], "name") == 0)
		order = BY_NAME;

	nstudes = readStudents(stdin, students);
	sortStudents(students, nstudes, order);
	showStudents(stdout, students, nstudes);
}

static void swap(Student *stu, int i, int j)
{
	Student temp = stu[i];
	stu[i] = stu[j];
	stu[j] = temp;
}

static bool less(Student s1, Student s2, Ordering order)
{
	if (order == BY_ZID || strcmp(s1.name, s2.name) == 0)
		return s1.zid < s2.zid;
	else if (order == BY_NAME || s1.zid == s2.zid)
		return strcmp(s1.name, s2.name) < 0;

	fprintf(stderr, "This should be impossible.\n");
	exit(EXIT_FAILURE);
}

// Sort "n" records in the "stu" array by order
// Always in ascending order
// If order == BY_ZID, sort numerically on unique "zid" field
// If order == BY_NAME, sort lexicographically on "name" field
//    if names are equal, sort in ascending order on "zid" field
void sortStudents(Student *stu, int n, Ordering order)
{
	if (stu == NULL || n <= 1 || (order != BY_ZID && order != BY_NAME))
		return;

	bool swapped = true;
	int passes = 0;
	while (swapped == true)
	{
		swapped = false;
		for (int i = 0; i < n - 1; i++)
		{
			if (less(stu[i + 1], stu[i], order) == true)
			{
				swap(stu, i + 1, i);
				swapped = true;
			}
			passes++;
		}
	}
}

// Read student records from file "in"
// Read into array of student records "stu"
// Returns number of records read
int readStudents(FILE *in, Student *stu)
{
	char line[MAXLINE];
	int  n, nread = 0;

	while (fgets(line, MAXLINE, in) != NULL)
	{
		// pointer to current student record
		Student *s = &stu[nread];
		n = sscanf(line, "%d:%[^:]:%d:%f",
			&(s->zid), &(s->name[0]), &(s->program), &(s->wam));
		if (n != 4)
		{
			fprintf(stderr, "Bad input: %s", line);
			exit(1);
		}
		nread++;
	}
	return nread;
}

// Print student info on standard output
// Info comes from array "stu" of student records
//   which contains "n" entries
void showStudents(FILE *out, Student *stu, int n)
{
	for (int i = 0; i < n; i++)
	{
// pointer to current student record
		Student *s = &stu[i];
			// should use MAXNAME, rather than 40
		fprintf(out, "%-7d %-40s %04d %0.1f\n",
			s->zid, s->name, s->program, s->wam);
	}
}
