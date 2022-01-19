#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Movies {
private:
	
	int id;
	float point;
	string name;
	int year;
	
public:
	Movies(int id, float point, string name, int year) 
	{
		this->id = id;
		this->point = point;
		this->name = name;
		this->year = year;
	}	
		
	Movies () {}
	
	int getId() const {
		return id;
	}
	
	void setId(int id) {
		Movies::id = id;
	}
	
	void setName(const string &name) {
		Movies::name = name;
	}
	
	void setYear(int year) {
		Movies::year = year;
	}
	const string &getName() const {
		return name;
	}
	
	float getPoint () const {
		return point;
	}
	
	void setPoint(float point) {
		Movies::point = point;
	}
	
	int getYear() const {
		return year;
	}
	
	void printMovie() {
        cout << "Point : " << point << " Name : " << name << " Year : " << year << endl;
    }
	
};

void getDetails(Movies movies[250],int identitiy) {
    for (int i = 0; i < 250; i++) {
        if (movies[i].getId() == identitiy)
        {
            movies[i].printMovie();
        }
    }
}

void listOfMovies(Movies movies[250],int year1, int year2) {
    if (year2 > year1) {
        for (int i = year1 ; i <= year2; i++) {
        	for(int j=0; j<250; j++) {
        		if(movies[j].getYear() <= year2 && movies[j].getYear() >= year1 ) {
                	movies[j].printMovie();
            	}
			}
        }
    } else {
    	for (int i = year2 ; i <= year1; i++) {
    		for(int j=0; j<250 ; j++) {
    			if(movies[j].getYear() <= year1 && movies[j].getYear() >= year2 ) {
            		movies[j].printMovie();
            	}
			}
        }
	}
}

void changePoint(Movies movies[250],int identitiy) {
	int new_point;
	cout << "Enter new point" << endl;
	cin >> new_point;
	
	for(int i=0; i<250; i++) {
		if(movies[i].getId() == identitiy) {
			cout << "before" << endl;
			movies[i].printMovie();
			movies[i].setPoint(new_point);
			cout << "after" << endl;
			movies[i].printMovie();
		}
	}
}

void firstletter (Movies movies[250]) {
    char x;
    cout << "Enter a letter" << endl;
    cin >> x;
    string str[250];
    for (int i = 0; i < 250; i++) {
        str[i] = movies[i].getName();
    }

    for (int i = 0; i < 250; i++) {
        if (str[i].at(0) == x){
            movies[i].printMovie();
        }
    }
}

void votingSystem(Movies movies[250],int identitiy) {
	cout << "You can only enter 10 value (1-10)" << endl;
	float point = movies[identitiy].getPoint();
	int x;
	int counter = 1;
	int exitValue = -1;
	for(int i=0; i<10; i++) {
		cout << "If the values is over write -1." << endl;
		cin >> x;
		
		if(x == exitValue) {
			break;
		}
		
		point += x;
		counter++;
	}
	
	float averageValue = (float)(point / counter);
	movies[identitiy].setPoint(averageValue);
	movies[identitiy].printMovie();
	
}

int main () {
	ifstream read_file;
	read_file.open("movies.txt");
	
	if(!read_file.is_open()) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	
	string line;
	string point;
	string name;
	string year;
	int id;
	
	Movies movie_list[250];
	int counter = 0;
	
	while (getline(read_file, line)) {
		stringstream line_stream(line);
		
		getline(line_stream, point, ';');
		getline(line_stream, name, '(');
		getline(line_stream, year, ')');
		
		float new_point = stof(point);
		int new_year = stoi(year);
		
		id = counter+1;
		
		movie_list[counter] = {id,new_point,name,new_year};
		counter++;
	}
	read_file.close();
	
	cout << "Welcome to the Movie Market." << endl;
	cout << "1 - Get movie details by ID"<< endl;
	cout <<	"2 - List movies between the years entered"<< endl;
	cout <<	"3 - Change the point of a movie"<< endl;
	cout <<	"4 - Get movie details starting with the entered letter"<< endl;
	cout <<	"5 - Exit" << endl;

	cout << "Please select an option." << endl;
    int num;
    cin >> num;
    
    if(num == 1) {
        int id;
        cout << "Enter id of the movie to learn the details." << endl;
        cin >> id;
        getDetails(movie_list,id);
    }
    if(num == 2) {
        int y1,y2;
        cout << "Which years films should be listed?" << endl;
        cin >> y1;
        cin >> y2;
        listOfMovies(movie_list,y1,y2);
    }
    if(num == 3) {
        int y;
        cout << "Which movie's point do you want to change ?" << endl;
        cin >> y;
        changePoint(movie_list,y);
    }
    if(num == 4) {
        firstletter(movie_list);
    }
    if(num == 5) {
        cout << "Which movie do you want to calculate the average point?" << endl;
    	int c;
    	cin >> c;
    	votingSystem(movie_list,c);
    }
    if(num == 6) {
		return 0;
    	
	}
	return 0;
}
