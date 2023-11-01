#include "File_Helper.h"

File_Helper::File_Helper()
{
    status = Checking_Path();

    switch (status) {
    case 1:
        cout << "Data creates" << endl;
        break;
    case 0:
        cout << "User exet the program" << endl;
        return;
    default:
        cerr << "Mistake in Checking_Path()" << endl;
        return;
    };
}

int File_Helper::Get_Status() { return status; }

vector<string> File_Helper::Get_Data()
{
    return data;
}

void File_Helper::Enter_Path()
{
	cout << "Please, input the file path:" << endl;
	cin >> this->path;
}

int File_Helper::Checking_Path()
{
    int res = -1;
    std::string line;

    Enter_Path();
    ifstream inputFile(path);

    if (inputFile) {
        cout << "Path " << path << " exist." << endl;
        

        while (getline(inputFile, line)) {
            if (line == "" || line == " ") continue;
            data.push_back(line);
        }
        inputFile.close();
        return res = 1;
    }
    else {
        cerr << "Path " << path << " not exist or can't be opened." << endl;
        cout << "Whould you like to download data again?" << endl << "1 - yes" << endl << "2 - no" << endl;
        string input_res;
        cin >> input_res;
        switch (stoi(input_res)) {
        case 1:
            res = Checking_Path();
            return res;
        case 2:
            cout << "Have a good day!" << endl;
            return res = 0;
        default:
            cout << "You input wrong number. Restart the program if ypu want to try again" << endl;
            return res = 0;
        }
    }
}
