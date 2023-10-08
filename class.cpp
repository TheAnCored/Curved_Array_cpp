#include "hclass.hpp"


List *List::NewList(size_t length){

	List *new_list = new List;


	new_list->length_list = length;

    for(size_t i=1;i<=new_list->length_list;i++){
		if(i==1){
			Link *first_link = new Link;

			new_list->first = first_link;
			new_list->current = new_list->first;
		}
		else if(i<new_list->length_list){
			Link *new_link = new Link;

			new_list->current->next_link = new_link;
			new_list->current = new_link;
		}
		else{
			Link *last_link = new Link;
			new_list->current->next_link = last_link;

			new_list->last = last_link;
		}
	}

	return new_list;
}

void List::Delete(List *list){

	Link *tmp;


	for(int i=1;i<=list->length_list;i++){
		if(i==1){
			list->current = list->first->next_link;
			delete list->first;
		}
		else if(i<=list->length_list-1){
			tmp = list->current->next_link;
			delete list->current;
			list->current = tmp;
		}
		else{
			delete list->last;
		}
	}
	delete list;
}

void List::PopStart(List *list){

	list->current= list->first->next_link;

	delete list->first;

	list->first = list->current;

	list->length_list--;
}

void List::PopEnd(List *list){

	if(list->length_list>1){
		for(int i=1;i<=list->length_list-1;i++){
			if(i==1){
				list->current = list->first;
			}
			else{
				list->current = list->current->next_link;
				
				if(i==list->length_list-1){
					delete list->last;

					list->last = list->current;

					list->length_list--;
				}
			}
		}
	}
	else{
		delete list->first;
		
		list->length_list=0;
	}
}

void List::PopLink(List *list, int index){
	
	if(index <= list->length_list){

		Link *tmp;

		if(index == list->length_list || index == 1){
			if(index == 1 && index == list->length_list){
				delete list->first;
				list->length_list = 0;
			}
			else if(index == 1 && list->length_list>1){
				list->PopStart(list);
			}
			else{
				list->PopEnd(list);
			}
		}
		else{
			for(int i=1; i<=index-1;i++){
				if(i==1){
					list->current = list->first;
				}
				else{
					list->current = list->current->next_link;
				}
			}

			tmp = list-> current -> next_link -> next_link;

			delete list->current->next_link;

			list->current->next_link = tmp;

			list->length_list--;
		}
	}
}