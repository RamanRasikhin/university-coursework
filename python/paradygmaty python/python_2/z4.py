class FamilyTree:
    def __init__(self):
        self.family = {}

    def add_son_father(self, son, father):
        self.family[son] = father

    def find_grandfather(self, grandson):
        father = self.family.get(grandson)
        if father is None:
            return None
        return self.family.get(father)