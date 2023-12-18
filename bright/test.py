from termcolor import colored
# print(colored("User named '{}' already exists.".format(user.name),"red"))


class Tester:
    def __init__(self):
        self.testCount = 10
        self.passed = True
        self.data = "none" #file
        self.answerKey = [
                        "100",
                        "6",
                        "20",
                        "12",
                        "1",
                        "2",
                        "5",
                        "(5 (6 (7 8)))"]
        self.results = []
    
    def find_answer(self):
        
        for answer in self.answerKey:
            try:
                self.results.index(answer)
                print(colored("PASS  =   {}".format(answer), "green"))
            except ValueError:
                self.passed = False
                print(colored("FAIL  =   {}".format(answer),"red"))


    def run_tests(self, fileName):
        results = []
        with open(fileName,'r', encoding='utf-8',errors='replace') as yisp:
            results = yisp.readlines()

        self.results = [s.strip() for s in results] 
        print(self.results)
        self.find_answer()

        if(self.passed):
            print(colored("ALL TESTS PASSED","green"))
        else:
            print(colored("TEST FAILED","red"))


if __name__ == "__main__":
    
    yispOut = "yispResults.txt"
    results = Tester()

    results.run_tests(yispOut)