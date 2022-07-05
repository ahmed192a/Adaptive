package application;

import java.util.ArrayList;

import javafx.scene.control.Accordion;

public class GUI {
	public String manifest_id;
	public ArrayList<Accordion> acc_list;
	public ArrayList<String> acc_names;
	public GUI() {
		manifest_id = new String();
		acc_list = new ArrayList<>();
		acc_names = new ArrayList<>();
	}
}
