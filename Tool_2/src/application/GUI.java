package application;

import java.util.ArrayList;

import javafx.scene.control.Accordion;

public class GUI {
	public String manifest_id;
	public ArrayList<Accordion> process_list;
	public ArrayList<String> process_name;
	public GUI() {
		manifest_id = new String();
		process_list = new ArrayList<>();
		process_name = new ArrayList<>();
	}
}
