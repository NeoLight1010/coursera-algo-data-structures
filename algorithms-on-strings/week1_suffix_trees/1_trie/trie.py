# python3

class Node:
    def __init__(self, value: str):
        self.value = value
        self._children = {}

    def add_child(self, node):
        self._children[node.value] = node

    def child_by_value(self, value):
        return self._children[value]

    def has_child_with_value(self, value):
        return value in self._children.keys()

    def children_nodes(self):
        return self._children.values()


class Trie:
    def __init__(self):
        self.root = Node("")
        self._all_nodes = [self.root]

    def add_pattern(self, pattern):
        current_node = self.root

        for char in pattern:
            if current_node.has_child_with_value(char):
                current_node = current_node.child_by_value(char)
                continue

            new_node = Node(char)

            current_node.add_child(new_node)
            self._all_nodes.append(new_node)

            current_node = new_node


    def get_adjacency(self):
        result = []
        indices = self.__build_node_indices()

        def create_edge(parent, child):
            edge = (indices[parent], indices[child])
            result.append((edge, child.value))

        self.traverse_parent_child(create_edge)

        return result

    
    def __build_node_indices(self):
        result = {}

        for i, node in enumerate(self._all_nodes):
            result[node] = i

        return result


    def traverse_parent_child(self, do):
        queue = [self.root]

        while queue:
            current_node = queue.pop(0)

            for child in current_node.children_nodes():
                do(current_node, child)

                queue.append(child)


if __name__ == "__main__":
    trie = Trie()
    n_of_patterns = int(input())
    
    for _ in range(n_of_patterns):
        pattern = input()
        trie.add_pattern(pattern)

    adjacency = trie.get_adjacency()
    
    for e in adjacency:
        print("{}->{}:{}".format(e[0][0], e[0][1], e[1]))
