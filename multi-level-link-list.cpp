#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct CITY{
	char name[20];
	
	CITY* east;
	CITY* west;
	CITY* north;
	CITY* south;
}*start = NULL;

CITY* getCity(char name[]){
	CITY* newCity = (CITY*)malloc(sizeof(CITY));
	strcpy(newCity->name, name);
	newCity->east = newCity->west = newCity->south = newCity->north = NULL;
	
	return newCity;
}

// Melakukan link untuk dua city west dan east
void joinEastWest(CITY* eastCity, CITY* westCity){
	eastCity->west = westCity;
	westCity->east = eastCity;
}

// Melakukan link untuk dua city south dan north
void joinNorthSouth(CITY* northCity, CITY* southCity){
	northCity->south = southCity;
	southCity->north = northCity;
}

void deleteNorth(CITY* curr){
	CITY* temp = curr->north;
	curr->north = NULL;

	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	
	temp->south = NULL;
	free(temp);
	
	return;
}

void deleteSouth(CITY* curr){
	CITY* temp = curr->south;
	curr->south = NULL;

	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	
	temp->north = NULL;
	free(temp);
	
	return;
}

void deleteWest(CITY* curr){
	CITY* temp = curr->west;
	curr->west = NULL;

	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	
	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	
	temp->east = NULL;
	free(temp);
	
	return;
}

void deleteEast(CITY* curr){
	CITY* temp = curr->east;
	curr->east = NULL;

	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	
	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	
	temp->west = NULL;
	free(temp);
	
	return;
}

void deleteCity(CITY* curr){
	int input;
	while(true){
		printf("Choose Wich City to delete\n");
		printf("1. North\n");
		printf("2. East\n");
		printf("3. West\n");
		printf("4. South\n");
		printf("5. Cancel\n");
		printf(">> ");
		
		scanf("%d", &input);
		switch(input){
			case 1: 
				if(curr->north)
					deleteNorth(curr);
				break;
			case 2: 
				if(curr->east)
					deleteEast(curr);
				break;
			case 3: 
				if(curr->west)
					deleteWest(curr);
				break;
			case 4: 
				if(curr->south)
					deleteSouth(curr);
				break;
			case 5: return;
		}
	}
}

void mainMenu(){
	
	if(start == NULL){
		printf("No City Yet!\n");
	}
	
	CITY* curr = start;
	while(true){
		printf("Current City: %s\n", curr->name);
		printf("1. East\n");
		printf("2. West\n");
		printf("3. North\n");
		printf("4. South\n");
		printf("5. Delete\n");
		printf(">> ");
		int input;
		scanf("%d", &input); getchar();
		switch(input){
			case 1: 
				if(curr->east){
					curr= curr->east;
				} else{
					printf("No current in the east side\n");
				}
				break;
			case 2:
				if(curr->west){
					curr= curr->west;
				} else{
					printf("No current in the west side\n");
				}
				break;
			case 3:
				if(curr->north){
					curr= curr->north;
				} else{
					printf("No current in the north side\n");
				}
				break;
			case 4:
				if(curr->south){
					curr= curr->south;
				} else{
					printf("No current in the south side\n");
				}
				break;
			case 5: deleteCity(curr);
				
				break;
		}
		
	}
	
}



int main(){
	
	CITY* Jakarta = getCity("Jakarta");
	CITY* Tangerang = getCity("Tangerang");
	CITY* Bogor = getCity("Bogor");
	CITY* Semarang = getCity("Semarang");
	CITY* Bandung = getCity("Bandung");
	CITY* Surabaya = getCity("Surabaya");
	
	joinNorthSouth(Jakarta, Bogor);
	joinEastWest(Jakarta,Tangerang);
	joinEastWest(Semarang,Jakarta);
	joinEastWest(Surabaya,Semarang);
	joinEastWest(Bandung,Bogor);
	
	
	start = Jakarta;
	
	mainMenu();
	
	return 0;
}
