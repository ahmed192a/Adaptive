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
		      Main.Tree = ParseXML(Main.Data);
	}
	
	public Node ParseXML(String Data) {
		Node root = new Node(null,"root");  
		Node current = root;
		for(int Ptr = 0;Ptr < Data.length();Ptr++) {
			if(Character.isWhitespace(Data.charAt(Ptr)))continue;
			else if(Data.charAt(Ptr)=='<') {
				Ptr++;
				if(Ptr==Data.length())return null;
				else if(Data.charAt(Ptr) == '/'){
					Ptr++;
					String nextTag = get_tag(Data,Ptr);
					if(current.getTag().equals(nextTag)) {
						current = current.getParent();
						Ptr+=nextTag.length();
					}
					else return null;
				}
				else {
					String nextTag = get_tag(Data,Ptr);
					Ptr+=nextTag.length();
					if(hasChild(Data,Ptr+1)){
						current = current.addNode(new Node(current,nextTag));
					}
					else {
						int end = Ptr + 1;
						for(; end+1!=Data.length() && Data.charAt(end+1)!='<'&& Data.charAt(end+1)!='>';end++);
						if(end+1 == Data.length() || Data.charAt(end+1)=='>')return null;
						String Val= Data.substring(Ptr+1, end+1);
						Ptr = end;
						current = current.addNode(new Node(current,nextTag,Val));
					}
				}
			}
			else return null;
		}
		if(current != root)return null;
		else return root;
	}
	private String get_tag(String Data,int start) {
		int end = start;
		for(;end+1!=Data.length() && Data.charAt(end+1)!='<' && Data.charAt(end+1)!='>';end++);
		if(end + 1 == Data.length() || Data.charAt(end+1)=='<')return "ERROR";
		return Data.substring(start,end+1);
	}
	private boolean hasChild(String Data,int pos) {
		while(pos!=Data.length() && Character.isWhitespace(Data.charAt(pos)))pos++;
		if(pos == Data.length() || Data.charAt(pos) == '<')return true;
		else return false;
	}	
}	