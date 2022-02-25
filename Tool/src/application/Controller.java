package application;

import java.io.File;
import java.util.Scanner;
import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.*;



public class Controller
{
	@FXML
	public MenuItem load_mi;
	public MenuItem convert_mi;
	public MenuItem close_mi;

	public FileChooser FC = new FileChooser();
	public TabPane tabs;
	public TextArea indicator;
	
    public void initialize() {
        indicator.appendText("No File Loaded.");  
        convert_mi.setDisable(true);
        close_mi.setDisable(true);
    }
	public void load_mi_func(ActionEvent e) throws IOException {
		String data = new String();
		FC.setTitle("Load XML");
		FC.getExtensionFilters().add(new FileChooser.ExtensionFilter("XML","*.XML"));	
		File myObj = FC.showOpenDialog(Main.getPrimaryStage());
		Main.Direc = myObj.getPath().substring(0,myObj.getPath().length() - myObj.getName().length());
		if(myObj!=null) {
		    Scanner myReader = new Scanner(myObj);
		    while (myReader.hasNextLine()) 
		    {
		      data += myReader.nextLine()+'\n';
		    }
		    myReader.close();
		    Main.Data = data;
		    Main.Tree = Node.ParseXML(Main.Data);  
		    if(Main.Tree == null){
			    indicator.clear();
		        indicator.appendText("XML File Loaded but inconsistent,Correct it and Reload.");  
		        indicator.setStyle("text-area-background: orange;");

		    }
		    else {
			    indicator.clear();
		        indicator.appendText("XML File Loaded and Verified!.");  
		        indicator.setStyle("text-area-background: darkgreen;");
			    add_tab("XML",Main.Data);
			    load_mi.setDisable(true);
		        convert_mi.setDisable(false);
		        close_mi.setDisable(false);
		    }
		}
	}
	
	public void convert_mi_func(ActionEvent e) {
		if(generate(Main.Tree)) {
			indicator.clear();
	        indicator.appendText("Header Files Generated Successfully!");  
	        add_tab("Skeleton"," ");
	        add_tab("Proxy"," ");
	        indicator.setStyle("text-area-background: #8e58ee;");
	        convert_mi.setDisable(true);	
		}
	}

	public void close_mi_func(ActionEvent e) {
		tabs.getTabs().clear();
	    indicator.clear();
        indicator.appendText("No File Loaded.");  
        indicator.setStyle("text-area-background: #00008b;");
	    load_mi.setDisable(false);
        convert_mi.setDisable(true);
        close_mi.setDisable(true);
        Main.Tree = null;
        Main.Data = null;
	}

	private void add_tab(String name,String text) {
		Tab tab = new Tab(name);
		TextArea txt = new TextArea(text);
		txt.setEditable(false);
		tab.setStyle("-fx-background-color:lightgreen;");
		tab.setContent(txt);
		tabs.getTabs().add(tab);
	}

	public boolean generate(Node SI) {
		String name = SI.Search("Service-Interface","short-name").getVal();
		if(name == null)return false;
		name = name.replaceAll(" ", "");	
		name = name.replaceAll("\t", "");	
		name = name.replaceAll("\n", "");	
		Main.sFile = Main.Direc + name + "_skeleton.h";
		Main.pFile = Main.Direc + name + "_proxy.h";
		try {
		      File myObj = new File(Main.sFile);
		      if (!myObj.createNewFile()) {
		        myObj.delete();
		        myObj.createNewFile();
		      }
		    } catch (IOException e) {
		      e.printStackTrace();
		      return false;
		    }
		try {
		      File myObj = new File(Main.pFile);
		      if (!myObj.createNewFile()) {
		        myObj.delete();
		        myObj.createNewFile();
		      }
		    } catch (IOException e) {
		      e.printStackTrace();
		      return false;
		    }
		return true;
	}
}	