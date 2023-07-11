

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Elif Nida Kayaduman

using namespace std;
vector<vector<char>> createShape(const string& query) {
    vector<vector<char>> shapematrix;
    vector<char> shapeolusturma;
    char fill_char = ' ';
    for (int i = 1; i < query.length(); i++)
    {
        char c = query[i];

        if (c == 's' && isdigit(query[i - 1]))
        {
            int repeat = query[i - 1] - '0';
            for (int j = 0; j < repeat; j++)
            {
                shapeolusturma.push_back('*');
            }


        }
        else if (c == 'b' && isdigit(query[i - 1]))
        {
            int repeat = query[i - 1] - '0'; // rakamı al ve int'e çevir
            for (int j = 0; j < repeat; j++)
            {
                shapeolusturma.push_back('#');
            }

        }
        else if (c == '/')
        {
            shapematrix.push_back(shapeolusturma); // Son satırı ekle
            shapeolusturma.clear(); // shapeolusturma temizlenir
        }
        else if (c == '1' || c == '2' || c == '3' || c == '4' ||
            c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        {
            continue;
        }
        else if (isdigit(c))
        {
            int repeat = c - '0';
            fill_char = (query[i - 1] == 's') ? '*' : '#';
            for (int j = 0; j < repeat; j++)
            {
                shapeolusturma.push_back(fill_char);
            }
        }

        if (i == query.length() - 1 && !shapeolusturma.empty()) // Son satırı ekle (daha sonra / karakteri olmadan)
        {

            shapematrix.push_back(shapeolusturma);
        }

    }

    return shapematrix;
}

void printShape(const vector<vector<char>>& shapematrix) {
    for (int i = 0; i < shapematrix.size(); i++) {
        for (int j = 0; j < shapematrix[i].size(); j++) {
            cout << shapematrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<pair<int, int>> starpositionsintheshape(const vector<vector<char>>& shapematrix)
{
    vector<pair<int, int>> positions;
    for (int i = 0; i < shapematrix.size(); i++)
    {
        for (int j = 0; j < shapematrix[i].size(); j++)
        {
            if (shapematrix[i][j] == '*')
            {
                positions.push_back({ i, j });
            }
        }
    }
    return positions;
}

/* matrix.size() ifadesi, matrisin satır sayısını verir.
   matrix[0].size() ifadesi, matrisin ilk satırının sütun sayısını verir
   Bu, tüm diğer satırların da aynı sayıda sütuna sahip olacağı anlamına gelir, bu nedenle bu değer,
   tüm matrisin sütun sayısını belirler. 
*/
void findallvalidplacement(vector<vector<char>>& matrix, vector<vector<char>>& shape, vector<pair<int, int>> positions)
{
    int nrows = matrix.size();
    int ncols = matrix[0].size();
    vector<vector<pair<int, int>>> valid_placements;
    int shape_rows = shape.size();
    int shape_cols = shape[0].size();

    // Loop over each position in the matrix
    for (int row = 0; row < nrows; row++)
    {
        for (int col = 0; col < ncols; col++)
        {
            // Check if the position is valid (i.e. contains a "-")
            if (matrix[row][col] == '-')
            {
                bool valid_placement = true;
                vector<pair<int, int>> placement;

                // Loop over each position in the list of provided positions
                for (int i = 0; i < positions.size(); i++)
                {
                    int shape_row = positions[i].first;
                    int shape_col = positions[i].second;
                    int matrix_row = row + shape_row;
                    int matrix_col = col + shape_col;

                    // Check if the cell in the shape is a "*" and the corresponding cell in the matrix is empty
                    if (matrix_row >= nrows || matrix_col >= ncols || shape[shape_row][shape_col] == '*' && matrix[matrix_row][matrix_col] != '-')
                    {
                        valid_placement = false;
                        break;
                    }
                    // If the cell in the shape is a "*", add its coordinates to the placement vector
                    else if (shape[shape_row][shape_col] == '*')
                    {
                        placement.push_back({ matrix_row, matrix_col });
                    }
                }

                // If all provided positions are valid, add the placement to the vector of valid placements
                if (valid_placement && placement.size() == positions.size())
                {
                    valid_placements.push_back(placement);
                }
            }
        }
    }

    // Check if any valid placements were found
    if (valid_placements.empty())
    {
        cout << "No placements found." << endl;
    }
    else
    {
        // Print and store the valid placements
        for (int i = 0; i < valid_placements.size(); i++)
        {
            cout << "Placement number " << i + 1 << ":\n";
            for (int j = 0; j < valid_placements[i].size(); j++)
            {
                cout << "(" << valid_placements[i][j].first << "," << valid_placements[i][j].second << ") ";
            }
            cout << endl;
        }
    }
}



int main()
{

    vector<vector<char>> matrix;
    vector<vector<char>> shapematrix;
    string query;
    string filename;
    ifstream file;

    while (true)
    {
        cout << "Please enter the file name: " << endl;
        cin >> filename;
        file.open(filename);
        if (file.fail())
        {
            cout << "Could not open the file. Please enter a valid file name." << endl;
            continue;
        }
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vector<char> row(line.begin(), line.end());
                matrix.push_back(row);
            }
            file.close();
            break;
        }
    }

    bool valid_file = true;
    int rowsize = matrix[0].size();
    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() != rowsize)
        {
            cerr << "Error: Rows of matrix are not of equal length." << endl;
            valid_file = false;
            break;
        }

        for (int j = 0; j < matrix[i].size(); j++)
        {
            char c = matrix[i][j];
            if (c != '-' && c != '#')
            {
                cerr << "Error: Matrix contains invalid character(s)." << endl;
                valid_file = false;
                break;
            }
        }
        if (!valid_file)
        {
            break;
        }
    }

    if (valid_file)
    {
        cout << "The matrix file contains : " << endl;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        exit(1);
    }


    while (true)
    {
        cout << "Enter the string query for a shape, or \"Quit\" to terminate the program: " << endl;
        cin >> query;

        if (query == "Quit")
        {

            break;
        }

        shapematrix = createShape(query);

        if (shapematrix.size() > matrix.size() || shapematrix[0].size() > matrix[0].size())
        {
            cout << "No placements found." << endl;

            continue;
        } 


        if (shapematrix.size() <= matrix.size() || shapematrix[0].size() <= matrix[0].size())
        {

           // printShape(shapematrix);
            vector<pair<int, int>> positions = starpositionsintheshape(shapematrix);
           //  for (int i = 0; i < positions.size(); i++) //yildizin konumlari
           // {
           //     cout << "(" << positions[i].first << ", " << positions[i].second << ")" << endl;
           //  }

            findallvalidplacement(matrix, shapematrix, positions);

            continue;

        }
        if (query == "1s" && query.length() == 2)
        {
            // printShape(shapematrix);
            vector<pair<int, int>> positions = starpositionsintheshape(shapematrix);
            // for (int i = 0; i < positions.size(); i++) //yildizin konumlari
            // {
            //    cout << "(" << positions[i].first << ", " << positions[i].second << ")" << endl;
            // }

            findallvalidplacement(matrix, shapematrix, positions);

            continue;


        }


    }
    return 0;
}

