class Book:
    def __init__(self):
        self.users = []

    def add_user(self, user):
        self.users.append(user)

    def print_users(self):
        print("Wszyscy użytkownicy w książce:")
        for user in self.users:
            user.print()

    def print_active_users(self):
        print("Aktywni użytkownicy w książce:")
        for user in self.users:
            if user.is_active:
                user.print()

    def find_by_name(self, name):
        for user in self.users:
            if user.name == name:
                return user
        return None

    def get_count(self):
        print(f"Ilość użytkowników w książce: {len(self.users)}")