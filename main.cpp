#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std::string_literals;

class Book {
public:
    Book()
        : reaching_counter_(MAX_PAGE, 0) {
    }

    void Read(int user, int page) {
        int i = progress_.contains(user)
            ? progress_[user]
            : 0;

        while (i < page) {
            ++reaching_counter_[i++];
        }

        progress_[user] = page;
    }

    double Cheer(int user) {
        if (!progress_.contains(user)) {
            return 0;
        }

        // Счётчик всех пользователей
        const auto user_counter = static_cast<double>(progress_.size());

        if (user_counter == 1) {
            return 1;
        }

        return (user_counter - reaching_counter_[progress_[user] - 1]) / (user_counter - 1);
    }

private:
    static constexpr int MAX_PAGE = 1000;

    // Прогресс каждого пользователя - страница, которой он достиг.
    // progress_[i] - страница, которой достиг пользователь i.
    std::unordered_map<int, int> progress_;

    // Счётчик для каждой страницы - сколько пользователей её достигло, со смещением на единицу.
    // reaching_counter_[0] - столько пользователей достигло страницы 1,
    // reaching_counter_[1] - столько пользователей достигло страницы 2 и т. д.
    std::vector<int> reaching_counter_;
};

int main() {
    Book book;

    int query;
    std::cin >> query;

    while (query > 0) {
        --query;

        std::string command;
        std::cin >> command;

        if (command == "READ"s) {
            int user, page;
            std::cin >> user >> page;

            book.Read(user, page);
            continue;
        }

        if (command == "CHEER"s) {
            int user;
            std::cin >> user;

            std::cout << book.Cheer(user) << std::endl;
        }
    }
}
