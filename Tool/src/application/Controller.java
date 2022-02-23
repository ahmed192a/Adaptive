package application;

import java.io.File;
import java.util.Scanner;
import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.*;



public class Controller
{
	@FXML
	private MenuItem load_mi;
	private FileChooser FC = new FileChooser();
	
	public void load_mi_func(ActionEvent e) throws IOException {
		String data = new String();
		FC.setTitle("Load XML");
		FC.getExtensionFilters().addAll(
				new FileChooser.ExtensionFilter("XML","*.XML"),
				new FileChooser.ExtensionFilter("All Files","*.*")
				);	
			  File myObj = FC.showOpenDialog(Main.getPrimaryStage());
		      Scanner myReader = new Scanner(myObj);
		      while (myReader.hasNextLine()) 
		      {
		        data += myReader.nextLine()+'\n';
		      }
		      myReader.close();
		      Main.Data = data;
		      System.out.println(Main.Data);
	}
	
	public Node ParseXML(String Data) {
		Node root = new Node(null,"root");  
		Node current = root;
		for(int Ptr = 0;Ptr < Data.length();Ptr++) {
			if(Character.isWhitespace(Data.charAt(Ptr)))continue;
			else if(Data.charAt(Ptr)=='<') {
	
			}
			else return null;
		}
		return root;
	}
	
}	