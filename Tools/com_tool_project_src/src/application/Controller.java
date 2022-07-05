package application;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.stage.*;



public class Controller
{
	@FXML
	public BorderPane pane;
	public MenuItem new_mi;
	public MenuItem load_mi;
	public MenuItem save_mi;
	public MenuItem save_as_mi;
	public MenuItem close_all_mi;
	public MenuItem verify_mi;
	public MenuItem generate_mi;
	public FileChooser FC = new FileChooser();
	public TabPane tabs = new TabPane();
	public ImageView iv = new ImageView(new Image("bg.png"));
	public TextArea indicator;
	public int counter = 1;
	///////////////   GUI   Code   ///////////////
    public void initialize() {
    	iv.setFitWidth(600);
    	iv.setFitHeight(400);
    	pane.setCenter(iv);
        indicator.appendText("ARA::COM Editor Tool");  
        indicator.setStyle("text-area-background: Crimson;");
        tabs.getSelectionModel().selectedItemProperty().addListener(
    	    new ChangeListener<Tab>() {
    	        @Override
    	        public void changed(ObservableValue<? extends Tab> ov, Tab t, Tab t1) {
    	        	if(tabs.getTabs().size()>0) {
					    indicator.clear();
					    String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
					    if(Path == null) {
					        indicator.appendText("Current File Path: \"Unsaved File\""); 
					    }
					    else {
					        indicator.appendText("Current File Path: \""+Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText())+"\""); 
					    }
				        indicator.setStyle("text-area-background: #c86464;");
    	        	}
    	        	refresh();
    	        }
    	    }
    	);
    }
    public void refresh() {
		if(tabs.getTabs().isEmpty()) {
	    	iv.setFitWidth(600);
	    	iv.setFitHeight(400);
	    	pane.setCenter(iv);
		    indicator.clear();
	        indicator.setStyle("text-area-background: #323278;"); 
	        indicator.appendText("No Current Files.");  
	        
			save_mi.setDisable(true);
			save_as_mi.setDisable(true);
	        close_all_mi.setDisable(true);
	        verify_mi.setDisable(true);
	        generate_mi.setDisable(true);
	        counter = 1;
		}
		else {
			pane.setCenter(tabs);
			save_mi.setDisable(false);
			save_as_mi.setDisable(false);
	        close_all_mi.setDisable(false);
	        verify_mi.setDisable(false);
	        generate_mi.setDisable(true);
		}
	}
	private void add_tab(String name,String text) {
		Tab tab = new Tab(name);
		TextArea txt = new TextArea(text);
		tab.setContent(txt);
		tabs.getTabs().add(tab);
		txt.setOnKeyTyped(new EventHandler<Event>() {
			 @Override
			    public void handle(Event e) {
				    indicator.clear();
				    String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
				    if(Path == null) {
				        indicator.appendText("*Editing*   Current File Path: \"Unsaved File\""); 
				    }
				    else {
				        indicator.appendText("*Editing*   Current File Path: \""+Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText())+"\""); 
				    }
			        indicator.setStyle("text-area-background: #c86464;");
			    }
		});
		tab.setOnClosed(new EventHandler<Event>() {
			 @Override
			    public void handle(Event e) {
				 	Main.Locations.remove(tab.getText());
				    indicator.clear();
			        indicator.appendText("File \""+tab.getText()+"\" Has Been Closed."); 
			        indicator.setStyle("text-area-background: #ff8000;");
			        refresh();
			    }
		});
	}
    public void new_mi_func(ActionEvent e) {
		String tab_name;
		if(counter == 1) tab_name = "New_File";
		else tab_name = "New_File_"+Integer.toString(counter);
		add_tab(tab_name,"");
		counter++;
		Main.Locations.put(tab_name, null);
	    indicator.clear();
        indicator.appendText("New File Created Successfully!");  
        indicator.setStyle("text-area-background: DarkGreen;");
		refresh();
	}
	public void load_mi_func(ActionEvent e) throws IOException {
		String data = new String();
		FC.setTitle("Load File");
		FC.getExtensionFilters().clear();
		FC.getExtensionFilters().addAll(
				new FileChooser.ExtensionFilter("XML File","*.XML"),
				new FileChooser.ExtensionFilter("All Files","*.*")
				);	
		File myObj = FC.showOpenDialog(Main.getPrimaryStage());
		if(myObj!=null) {
			if(Main.Locations.containsValue(myObj.getPath())){
				indicator.clear();
		        indicator.appendText("File Already Opened!");  
		        indicator.setStyle("text-area-background: #ff8000;");
			}
			else {
			    Scanner myReader = new Scanner(myObj);
			    while (myReader.hasNextLine()) data += myReader.nextLine()+'\n';
			    myReader.close();
			    Main.Locations.put(myObj.getName(),myObj.getPath());	
			    add_tab(myObj.getName(),data);
			    indicator.clear();
		        indicator.appendText("File Loaded Successfully!");  
		        indicator.setStyle("text-area-background: DarkGreen;");
			}
		}
		refresh();
	}
	public void save_mi_func(ActionEvent e) throws IOException{
		Tab current = tabs.getSelectionModel().getSelectedItem();
		TextArea txt = (TextArea) current.getContent();
		String Path = Main.Locations.get(current.getText());
		if(Path == null) {
			FC.setTitle("Save File As");
			FC.setInitialFileName(current.getText());
			FC.getExtensionFilters().clear();
			int period = current.getText().lastIndexOf(".");
			String ext;
			if(period == -1) ext = "null";
			else ext = current.getText().substring(period);
			FC.getExtensionFilters().add(new FileChooser.ExtensionFilter(ext,"*"+ext));	
			File myObj = FC.showSaveDialog(Main.getPrimaryStage());
			if(myObj!=null) {
				PrintWriter myWriter = new PrintWriter(myObj);
				myWriter.println(txt.getText());
				myWriter.close();
				Main.Locations.remove(current.getText());
				tabs.getTabs().remove(tabs.getSelectionModel().getSelectedIndex());
				add_tab(myObj.getName(), txt.getText());
			    Main.Locations.put(myObj.getName(),myObj.getPath());	    
			    indicator.clear();
		        indicator.setStyle("text-area-background: Indigo;");
		        indicator.appendText("File Saved in: "+ myObj.getPath());  
			}
		}
		else {
			WriteFile(Path,txt.getText());
			indicator.clear();
	        indicator.setStyle("text-area-background: Indigo;");
	        indicator.appendText("File Overwritten Successfully!");  
		}
		refresh();
	}
	public void save_as_mi_func(ActionEvent e) throws IOException {
		Tab current = tabs.getSelectionModel().getSelectedItem();
		TextArea txt = (TextArea) current.getContent();
		FC.setTitle("Save File As");
		FC.setInitialFileName(current.getText());
		FC.getExtensionFilters().clear();
		int period = current.getText().lastIndexOf(".");
		String ext;
		if(period == -1) ext = "null";
		else ext = current.getText().substring(period);
		FC.getExtensionFilters().add(new FileChooser.ExtensionFilter(ext,"*"+ext));			
		File myObj = FC.showSaveDialog(Main.getPrimaryStage());
		if(myObj!=null) {
			PrintWriter myWriter = new PrintWriter(myObj);
			myWriter.println(txt.getText());
			myWriter.close();
			Main.Locations.remove(current.getText());
			tabs.getTabs().remove(tabs.getSelectionModel().getSelectedIndex());
			add_tab(myObj.getName(), txt.getText());
		    Main.Locations.put(myObj.getName(),myObj.getPath());	    
		    indicator.clear();
	        indicator.setStyle("text-area-background: Indigo;");
	        indicator.appendText("File Saved in: "+ myObj.getPath());  
		}
		refresh();
	}
	public void close_all_mi_func(ActionEvent e) {
		tabs.getTabs().clear();
		Main.Locations.clear();
        Main.Tree = null;
        refresh();
	}
	public void verify_mi_func(ActionEvent e) {
		String tab_name = tabs.getSelectionModel().getSelectedItem().getText();
		if(tab_name.lastIndexOf(".")==-1) {
			indicator.clear();
	        indicator.appendText("Current File is Not in XML Format \"*.XML\"");  
	        indicator.setStyle("text-area-background: DarkSalmon;");
	        return;
		}
		String ext = tab_name.substring(tab_name.indexOf(".")+1);
		if(!ext.equals("xml")){
			indicator.clear();
	        indicator.appendText("Current File is Not in XML Format \"*.XML\"");  
	        indicator.setStyle("text-area-background: DarkSalmon;");
	        return;
		}
		String data = ((TextArea)tabs.getSelectionModel().getSelectedItem().getContent()).getText();
	    Main.Tree = Node.ParseXML(data);  
	    if(Main.Tree == null){
		    indicator.clear();
	        indicator.appendText("XML File is inconsistent,Correct it and Reverify.");  
	        indicator.setStyle("text-area-background: DarkSalmon;");
	    }
	    else {
		    indicator.clear();
	        indicator.appendText("XML File Loaded and Verified!");  
	        indicator.setStyle("text-area-background: DarkGreen;");
	        generate_mi.setDisable(false);
	    }
	}
	public void generate_mi_func(ActionEvent e) {
		ArrayList<Node> SIGroup = Main.Tree.Search("Service-Interface");
		for(Node SI : SIGroup) {
			if(generate_skeleton(SI) && generate_proxy(SI) && generate_common(SI) && generate_returntypes(SI)) {
		        if(SIGroup.get(SIGroup.size()-1).equals(SI)) {
					indicator.clear();
			        indicator.setStyle("text-area-background: DarkGreen;");
			        indicator.appendText("Header Files Generated Successfully!");  
			        refresh();
		        }
			}
		}
	}
	///////////////   Algorithm Code   ///////////////
	public boolean generate_skeleton(Node SI) {
		String name = SI.Search("short-name").get(0).getVal();
		if(name == null) return false;
		name = c_get(name);	

		String full_name = new String();
		ArrayList<Node> tmp = SI.Search("namespace","symbol-probs","symbol");
		ArrayList<String> sym = new ArrayList<String>();
		for(Node i:tmp) {
			sym.add(c_get(i.getVal()));
			full_name+=sym.get(sym.size()-1).toUpperCase()+"_";
		}
		full_name += name.toUpperCase();
		sym.add("skeleton");
		

		String Data = new String(
				"#ifndef "+full_name+"_SKELETON_H\r\n"
			      		+ "#define "+full_name+"_SKELETON_H\r\n"
			      		+ "#include <string.h>\r\n"
			      		+ "#include <future>\r\n"
			      		+ "#include \"com/proxy_skeleton/skeleton/service_skeleton.h\"\r\n"
			      		+ "#include \"com/proxy_skeleton/definitions.h\"\r\n"
			      		+ "//#include \r\n"
			      		+ "\r\n"
				);
		
		//Start
		for(String i:sym) {
			Data+=  "namespace "+i+"\r\n"+ "{\r\n";
		}
		
		
		//Events
		ArrayList<Node> events = SI.Search("events","variable-data-probs");
		Data+= "namespace events\r\n{\r\n";
		for(Node event : events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			String prename = "";
			for(String i:sym) {
				if(i.equals("skeleton"))continue;
				prename+="::"+i;
			}
			prename +="::"+ename;
			Data+= "using "+ ename +"_e = ara::com::proxy_skeleton::skeleton::Event<"+prename+">;\r\n";

		}
		Data+= "}\r\n";
		
		//Fields
		ArrayList<Node> fields = SI.Search("fields","field");
		Data+= "namespace fields\r\n{\r\n";
		for(Node field : fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			String f_g = c_get(field.Search("has-getter").get(0).getVal());
			String f_s = c_get(field.Search("has-setter").get(0).getVal());
			String f_n = c_get(field.Search("has-notifier").get(0).getVal());
			String prename = "";
			for(String i:sym) {
				if(i.equals("skeleton"))continue;
				prename+="::"+i;
			}
			prename +="::"+fname;

			Data+= "using "+ fname +"_f = ara::com::proxy_skeleton::skeleton::FieldType<"+prename+", "+f_g+", "+f_s+", "+f_n+">::type;\n"; 

		}
		Data+= "}\r\n";
	
		//Class
		Data+="class "+name+"_skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton\r\n"
				+ "{\r\n"
				+ "public:\r\n"
				+ name +"_skeleton(\r\n"
				+ "ara::com::InstanceIdentifier instance,\r\n"
				+ "ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent) : ara::com::proxy_skeleton::skeleton::ServiceSkeleton(\""+ name +"_skeleton\", instance, mode),\r\n";
		for(Node event:events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			Data+=ename+"(this,\""+ename+"\"),\r\n";
		}
		for(Node field:fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			Data+=fname+"(this,\""+fname+"\"),\r\n";
		}	
		Data=Data.substring(0, Data.lastIndexOf(','));
		Data+= "{}\r\n"
				+ "~"+name+"_skeleton();\r\n";
		for(Node event:events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			Data+="events::"+ename+"_e "+ename+";\r\n";
		}
		for(Node field:fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			Data+="fields::"+fname+"_f "+fname+";\r\n";
		}		
		
		ArrayList<Node> methods = SI.Search("methods","client-server-operation");
        ArrayList<String> includes = new ArrayList<String>();
		for(Node method : methods) {
			String m_n = c_get(method.Search("short-name").get(0).getVal());
			ArrayList<Node> args = method.Search("arguments","argument-probs");
			String m_a = "";
			for(Node arg:args) {
				String t = c_get((arg.Search("type").get(0).getVal()));
				if(t.contains("/")) {
					String inc = t.substring(0,t.lastIndexOf('/'));
					if(!includes.contains(inc)) {
						includes.add(inc);
						Data = Data.replace("//#include", "#include \""+inc+".h\"\r\n//#include");
					}
					m_a+=t.substring(t.lastIndexOf('/') + 1);
				}
				else {
					m_a+=t;
				}
								
				m_a += arg.Search("direction").get(0).getVal().contains("out")? " &":" ";
				m_a += c_get((arg.Search("short-name").get(0).getVal())) + ",";
			}
			m_a = m_a.substring(0, m_a.lastIndexOf(','));
			Data+="void "+m_n+"("+ m_a +");\r\n";
		}

		Data+= "};\r\n";
		//Finish
		for(int i =0;i<sym.size();i++)	Data+=  "}\r\n";
		Data+= "#endif";
		Data = Data.replace("//#include", "");
		
		String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
		String Directory = Path.substring(0,Path.lastIndexOf("\\")+1);
		String New_Path = Directory + name + "_skeleton.h";
		if(WriteFile(New_Path,Data)) {
			Main.Locations.put(name + "_skeleton.h", New_Path);
			add_tab(name + "_skeleton.h",Data);
			return true;
		}
		else return false;
	}
	public boolean generate_proxy(Node SI) {
		String name = SI.Search("short-name").get(0).getVal();
		if(name == null) return false;
		name = c_get(name);	

		String full_name = new String();
		ArrayList<Node> tmp = SI.Search("namespace","symbol-probs","symbol");
		ArrayList<String> sym = new ArrayList<String>();
		for(Node i:tmp) {
			sym.add(c_get(i.getVal()));
			full_name+=sym.get(sym.size()-1).toUpperCase()+"_";
		}
		full_name += name.toUpperCase();
		sym.add("proxy");
		

		String Data = new String(
				"#ifndef "+full_name+"_PROXY_H\r\n"
			      		+ "#define "+full_name+"_PROXY_H\r\n"
			      		+ "#include <string.h>\r\n"
			      		+ "#include <future>\r\n"
			      		+ "#include \"com/proxy_skeleton/proxy/service_proxy.h\"\r\n"
			      		+ "#include \"com/proxy_skeleton/definitions.h\"\r\n"
			      		+ "#include \""+name+"_common.h\"\r\n"
			      		+ "\r\n"
				);
		
		//Start
		for(String i:sym) {
			Data+=  "namespace "+i+"\r\n"+ "{\r\n";
		}
		
		
		//Events
		ArrayList<Node> events = SI.Search("events","variable-data-probs");
		Data+= "namespace events\r\n{\r\n";
		for(Node event : events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			String prename = "";
			for(String i:sym) {
				if(i.equals("proxy"))continue;
				prename+="::"+i;
			}
			prename +="::"+ename;
			Data+= "using "+ ename +"_e = ara::com::proxy_skeleton::proxy::Event<"+prename+">;\r\n";

		}
		Data+= "}\r\n";
		
		//Fields
		ArrayList<Node> fields = SI.Search("fields","field");
		Data+= "namespace fields\r\n{\r\n";
		for(Node field : fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			String f_g = c_get(field.Search("has-getter").get(0).getVal());
			String f_s = c_get(field.Search("has-setter").get(0).getVal());
			String f_n = c_get(field.Search("has-notifier").get(0).getVal());
			String prename = "";
			for(String i:sym) {
				if(i.equals("proxy"))continue;
				prename+="::"+i;
			}
			prename +="::"+fname;

			Data+= "using "+ fname +"_f = ara::com::proxy_skeleton::proxy::FieldType<"+prename+", "+f_g+", "+f_s+", "+f_n+">::type;\n"; 

		}
		Data+= "}\r\n";
		
		//Methods
		ArrayList<Node> methods = SI.Search("methods","client-server-operation");
		Data+= "namespace methods\r\n{\r\n";
		for(Node method : methods) {
			String mname = c_get(method.Search("short-name").get(0).getVal());
			String prename = "";
			for(String i:sym) {
				if(i.equals("proxy"))continue;
				prename+=i+"::";
			}
			prename += mname;
			Data+= "using "+ mname +"_m = "+prename+";\r\n";
		}
		Data+= "}\r\n";
		
	
		//Class
		Data+="class "+name+"_proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy\r\n"
				+ "{\r\n"
				+ "public:\r\n"
				+ "using HandleType = ara::com::proxy_skeleton::proxy::ServiceProxy::HandleType;\r\n"
				+ name +"_proxy(HandleType handle) : ara::com::proxy_skeleton::proxy::ServiceProxy(\""+ name +"_proxy\", handle),\r\n";
		for(Node event:events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			Data+=ename+"(this,\""+ename+"\"),\r\n";
		}
		for(Node field:fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			Data+=fname+"(this,\""+fname+"\"),\r\n";
		}	
		for(Node method:methods) {
			String mname = c_get(method.Search("short-name").get(0).getVal());
			Data+=mname+"(this),\r\n";
		}	
		Data=Data.substring(0, Data.lastIndexOf(','));
		Data+= "{}\r\n"
				+ "~"+name+"_proxy();\r\n";
		for(Node event:events) {
			String ename = c_get(event.Search("short-name").get(0).getVal());
			Data+="events::"+ename+"_e "+ename+";\r\n";
		}
		for(Node field:fields) {
			String fname = c_get(field.Search("short-name").get(0).getVal());
			Data+="fields::"+fname+"_f "+fname+";\r\n";
		}		
		
		for(Node method : methods) {
			String m_n = c_get(method.Search("short-name").get(0).getVal());
			Data+="methods::"+m_n+"_m "+ m_n +";\r\n";
		}

		Data+= "};\r\n";
		//Finish
		for(int i =0;i<sym.size();i++)	Data+=  "}\r\n";
		Data+= "#endif";
		Data = Data.replace("//#include", "");
		String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
		String Directory = Path.substring(0,Path.lastIndexOf("\\")+1);
		String New_Path = Directory + name + "_proxy.h";
		if(WriteFile(New_Path,Data)) {
			Main.Locations.put(name + "_proxy.h", New_Path);
			add_tab(name + "_proxy.h",Data);
			return true;
		}
		else return false;
	}
	public boolean generate_common(Node SI) {
		String name = SI.Search("short-name").get(0).getVal();
		if(name == null) return false;
		name = c_get(name);	

		String full_name = new String();
		ArrayList<Node> tmp = SI.Search("namespace","symbol-probs","symbol");
		ArrayList<String> sym = new ArrayList<String>();
		for(Node i:tmp) {
			sym.add(c_get(i.getVal()));
			full_name+=sym.get(sym.size()-1).toUpperCase()+"_";
		}
		full_name += name.toUpperCase();		

		String Data = new String(
				"#ifndef "+full_name+"_COMMON_H\r\n"
			      		+ "#define "+full_name+"_COMMON_H\r\n"
			      		+ "#include \""+name+"_returntypes.h\"\r\n"
			      		+ "#include \"com/proxy_skeleton/proxy/service_proxy.h\"\r\n"
			      		+ "//#include \r\n"
			      		+ "\r\n"
				);
		
		//Start
		for(String i:sym) {
			Data+=  "namespace "+i+"\r\n"+ "{\r\n";
		}
		
		
		//Methods
		ArrayList<Node> methods = SI.Search("methods","client-server-operation");
		ArrayList<String> includes = new ArrayList<String>();
		for(Node method : methods) {
			
			String m_n = c_get(method.Search("short-name").get(0).getVal());
			Data += "class "+m_n+"\r\n{\r\n";
			Data += "private:\r\n"
					+ "ara::com::proxy_skeleton::proxy::ServiceProxy *m_srv;\r\n"
					+ "public:\r\n"
					+ m_n + "(ara::com::proxy_skeleton::proxy::ServiceProxy *srv):m_srv{srv}{}\r\n";
			for(String i:sym) {
				Data+= i+"::";
			}
			
			ArrayList<Node> args = method.Search("arguments","argument-probs");
			String m_a = "";
			for(Node arg:args) {
				if(!arg.Search("direction").get(0).getVal().contains("in"))continue;
				String t = c_get((arg.Search("type").get(0).getVal()));
				if(t.contains("/")) {
					String inc = t.substring(0,t.lastIndexOf('/'));
					if(!includes.contains(inc)) {
						includes.add(inc);
						Data = Data.replace("//#include", "#include \""+inc+".h\"\r\n//#include");
					}
					m_a+=t.substring(t.lastIndexOf('/') + 1);
				}
				else {
					m_a+=t;
				}
				m_a +=" "+ c_get((arg.Search("short-name").get(0).getVal())) + ",";
			}
			m_a = m_a.substring(0, m_a.lastIndexOf(','));
			Data += m_n +"ReturnType operator()(" + m_a +"){return result;}\r\n";
			for(String i:sym) {
				Data+= "::"+i;
			}
			Data +="::"+m_n+"ReturnType result;\r\n};\r\n";
		}

		for(int i =0;i<sym.size();i++)	Data+=  "}\r\n";
		Data = Data.replace("//#include", "");
		Data+= "#endif";
		String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
		String Directory = Path.substring(0,Path.lastIndexOf("\\")+1);
		String New_Path = Directory + name + "_common.h";
		if(WriteFile(New_Path,Data)) {
			Main.Locations.put(name + "_common.h", New_Path);
			add_tab(name + "_common.h",Data);
			return true;
		}
		else return false;
	}
	public boolean generate_returntypes(Node SI) {
		String name = SI.Search("short-name").get(0).getVal();
		if(name == null) return false;
		name = c_get(name);	

		String full_name = new String();
		ArrayList<Node> tmp = SI.Search("namespace","symbol-probs","symbol");
		ArrayList<String> sym = new ArrayList<String>();
		for(Node i:tmp) {
			sym.add(c_get(i.getVal()));
			full_name+=sym.get(sym.size()-1).toUpperCase()+"_";
		}
		full_name += name.toUpperCase();		

		String Data = new String(
				"#ifndef "+full_name+"_RETURNTYPES_H\r\n"
			      		+ "#define "+full_name+"_RETURNTYPES_H\r\n"
			      		+ "#include <future>\r\n"
			      		+ "//#include \r\n"
			      		+ "\r\n"
				);
		
		//Start
		for(String i:sym) {
			Data+=  "namespace "+i+"\r\n"+ "{\r\n";
		}
		
		
		//Methods
		ArrayList<Node> methods = SI.Search("methods","client-server-operation");
        ArrayList<String> includes = new ArrayList<String>();

		
		for(Node method : methods) {
			
			String m_n = c_get(method.Search("short-name").get(0).getVal());
			Data += "struct " + m_n+"ReturnType\r\n{\r\n";
			ArrayList<Node> args = method.Search("arguments","argument-probs");
			for(Node arg:args) {
				String m_a = "::";
				if(!arg.Search("direction").get(0).getVal().contains("out"))continue;
				String t = c_get((arg.Search("type").get(0).getVal()));
				if(t.contains("/")) {
					String inc = t.substring(0,t.lastIndexOf('/'));
					if(!includes.contains(inc)) {
						includes.add(inc);
						Data = Data.replace("//#include", "#include \""+inc+".h\"\r\n//#include");
					}
					m_a+=t.substring(t.lastIndexOf('/') + 1);
				}
				else {
					m_a+=t;
				}				
				m_a += " "+c_get((arg.Search("short-name").get(0).getVal()))+";\r\n";
				Data += m_a;
			}
			Data +="};\r\n";
		}
		for(int i =0;i<sym.size();i++)	Data+=  "}\r\n";
		Data = Data.replace("//#include", "");
		Data+= "#endif";
		String Path = Main.Locations.get(tabs.getSelectionModel().getSelectedItem().getText());
		String Directory = Path.substring(0,Path.lastIndexOf("\\")+1);
		String New_Path = Directory + name + "_returntypes.h";
		if(WriteFile(New_Path,Data)) {
			Main.Locations.put(name + "_returntypes.h", New_Path);
			add_tab(name + "_returntypes.h",Data);
			return true;
		}
		else return false;
	}
	public boolean WriteFile(String Path,String Text){
		File myObj = new File(Path);
        FileWriter myWriter;
		try {
			myWriter = new FileWriter(myObj);
			myWriter.write(Text);
	        myWriter.close();  
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	    return true;
	}
	public String c_get(String in) {
		in = in.replaceAll(" ", "");	
		in = in.replaceAll("\t", "");	
		in = in.replaceAll("\n", "");
		return in;
	}
}	