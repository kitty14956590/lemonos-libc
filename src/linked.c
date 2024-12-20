// credit: roadrunner

#include <linked.h>
#include <stdlib.h>

linked_t * linked_leaf(linked_t * bottom) {
	linked_t * top = bottom;
	while (top->next) {
		top = top->next;
	}
	return top;
}

linked_t * linked_branch(linked_t * node) {
	linked_t * p = node;
	while (p->back) {
		p = p->back;
	}
	return p;
}

int linked_count(linked_t * bottom) {
	if (!bottom) {
		return 0;
	}
	linked_t * current = bottom;
	int i = 0;
	while (current) {
		current = current->next;
		i++;
	}
	return i;
}

linked_t * linked_add(linked_t * bottom, void * p) {
	if (!bottom) {
		linked_t * new = malloc(sizeof(linked_t) + 8);
		new->p = p;
		new->next = 0;
		new->back = 0;
		return new;
	}
	linked_t * new = malloc(sizeof(linked_t) + 8);
	linked_t * leaf;
	if (!new) {
		return 0;
	}
	leaf = linked_leaf(bottom);
	new->p = p;
	new->next = 0;
	new->back = leaf;
	leaf->next = new;
	return bottom;
}

linked_t * linked_append(linked_t * bottom, linked_t * node) {
	linked_t * leaf;
	if (!node) {
		return 0;
	}
	if (!bottom) {
		return node;
	}
	leaf = linked_leaf(bottom);
	node->next = 0;
	node->back = leaf;
	leaf->next = node;
	return bottom;
}

linked_t * linked_get(linked_t * bottom, int index) {
	if (!bottom) {
		return 0;
	}
	linked_t * current = bottom;
	int i = 0;
	while (current) {
		if (i == index) {
			return current;
		}
		current = current->next;
		i++;
	}
	return 0;
}

linked_t * linked_remove(linked_t * bottom, int index) {
	return linked_delete(linked_get(bottom, index));
}

linked_t * linked_delete(linked_t * node) {
	linked_t * branch = linked_branch(node);
	linked_t * next = branch->next;
	if (node->back) {
		node->back->next = node->next;
	}
	if (node->next) {
		node->next->back = node->back;
	}
	free(node);
	return branch == node ? next : branch;
}

linked_t * linked_pop(linked_t * node) {
	linked_t * branch = linked_branch(node);
	linked_t * next = branch->next;
	if (node->back) {
		node->back->next = node->next;
	}
	if (node->next) {
		node->next->back = node->back;
	}
	return branch == node ? next : branch;
}

linked_t * linked_shift(linked_t * bottom, linked_t ** out) {
	if (!bottom) {
		*out = 0;
		return 0;
	}
	linked_t * next = bottom->next;
	if (next) {
		next->back = 0;
	}
	*out = bottom;
	return next;
}

void linked_iterate(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return;
	}
	linked_t * node = bottom;
	while (node) {
		callback(node, pass);
		node = node->next;
	}
}

void linked_destroy_all(linked_t * bottom, linked_callback_t destroy, void * pass) {
	if (!bottom) {
		return;
	}
	linked_t * node = bottom;
	while (node) {
		linked_t * next = node->next;
		destroy(node, pass);
		free(node);
		node = next;
	}
}

linked_t * linked_find(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return 0;
	}
	linked_t * node = bottom;
	while (node) {
		if (callback(node, pass)) {
			return node;
		}
		node = node->next;
	}
	return 0;
}

linked_t * linked_find_back(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return 0;
	}
	linked_t * node = linked_leaf(bottom);
	while (node) {
		if (callback(node, pass)) {
			return node;
		}
		node = node->back;
	}
	return 0;
}

// generic linked_find callback
int linked_find_generic(linked_t * node, void * pass) {
	return node->p == pass;
}
