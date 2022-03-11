package application;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

import javafx.event.ActionEvent;
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
	public MenuItem load_mi;
	public MenuItem convert_mi;
	public MenuItem close_mi;

	public FileChooser FC = new FileChooser();
	public TabPane tabs = new TabPane();
	public ImageView iv = new ImageView(new Image("bg.png"));
	
	public TextArea indicator;
	
    public void initialize() {
    	iv.setFitWidth(600);
    	iv.setFitHeight(400);
    	pane.setCenter(iv);
        indicator.appendText("No File Loaded.");  
        convert_mi.setDisable(true);
        close_mi.setDisable(true);
    }
	public void load_mi_func(ActionEvent e) throws IOException {
		String data = new String();
		FC.setTitle("Load XML");
		FC.getExtensionFilters().add(new FileChooser.ExtensionFilter("XML","*.XML"));	
		File myObj = FC.showOpenDialog(Main.getPrimaryStage());
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
				Main.Direc = myObj.getPath().substring(0,myObj.getPath().length() - myObj.getName().length());
			    indicator.clear();
		        indicator.appendText("XML File Loaded and Verified!.");  
		        indicator.setStyle("text-area-background: darkgreen;");
		        pane.setCenter(tabs);
			    add_tab("XML",Main.Data);
			    load_mi.setDisable(true);
		        convert_mi.setDisable(false);
		        close_mi.setDisable(false);
		    }
		}
	}
	public void convert_mi_func(ActionEvent e) throws FileNotFoundException {
		ArrayList<Node> SIGroup = Main.Tree.Search("Service-Interface");
		String names = new String();
		for(Node SI : SIGroup) {
			if(generate(SI) && generate_proxy(SI)) {
				indicator.clear();
		        String s = Main.sFile.get(Main.sFile.size()-1);
		        String p = Main.pFile.get(Main.sFile.size()-1);
		        add_tab(s.substring(s.lastIndexOf('\\') + 1),ReadFile(s));
		        add_tab(p.substring(s.lastIndexOf('\\') + 1),ReadFile(p));
		        names+="\"" + c_get(SI.Search("short-name").get(0).getVal())+"\",";
		        if(SIGroup.get(SIGroup.size()-1).equals(SI)) {
			        indicator.appendText("Header Files for "+ names.substring(0,names.length()-1) +" Generated Successfully!");  
			        indicator.setStyle("text-area-background: #8e58ee;");
			        convert_mi.setDisable(true);
		        }
			}
		}
	}
	public void close_mi_func(ActionEvent e) {
    	pane.setCenter(iv);
		tabs.getTabs().clear();
	    indicator.clear();
        indicator.appendText("No File Loaded.");  
        indicator.setStyle("text-area-background: #00008b;");
	    load_mi.setDisable(false);
        convert_mi.setDisable(true);
        close_mi.setDisable(true);
        Main.Tree = null;
        Main.Data = null;
        Main.File = null;
        Main.sFile.clear();
        Main.pFile.clear();
        Main.sData.clear();
        Main.pData.clear();
	}
	private void add_tab(String name,String text) {
		Tab tab = new Tab(name);
		tab.setClosable(false);
		TextArea txt = new TextArea(text);
		txt.setEditable(false);
		tab.setStyle("-fx-background-color:lightgreen;");
		tab.setContent(txt);
		tabs.getTabs().add(tab);
	}
	public boolean generate(Node SI) {
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
				"#ifndef "+full_name+"_SKELETON_H_\r\n"
			      		+ "#define "+full_name+"_SKELETON_H_\r\n"
			      		+ "#include <string.h>\r\n"
			      		+ "#include \"core/future.h\"\r\n"
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

		for(Node method : methods) {
			String m_n = c_get(method.Search("short-name").get(0).getVal());
			ArrayList<Node> args = method.Search("arguments","argument-probs");
			String m_a = "";
			for(Node arg:args) {
				String t = c_get((arg.Search("type").get(0).getVal()));
				if(t.contains("/")) {
					String inc = t.substring(0,t.lastIndexOf('/'));
					Data = Data.replace("//#include", "#include \""+inc+".h\"\r\n//#include");
					m_a+=t.substring(t.lastIndexOf('/') + 1);
				}
				else {
					m_a+=t;
				}
								
				m_a += arg.Search("direction").get(0).getVal().contains("out")? " &":" ";
				m_a += c_get((arg.Search("short-name").get(0).getVal())) + ",";
			}
			m_a = m_a.substring(0, m_a.lastIndexOf(','));
			Data+="ara::core::Future<void> "+m_n+"("+ m_a +");\r\n";
		}

		Data+= "};\r\n";
		//Finish
		for(String i:sym) {
			Data+=  "}\r\n";
		}
		Data+= "#endif";
		Data = Data.replace("//#include", "");

		Main.sFile.add(Main.Direc + name + "_skeleton.h");
		try {
		      File myObj = new File(Main.sFile.get(Main.sFile.size()-1));
		      if (!myObj.createNewFile()) {
		        myObj.delete();
		        myObj.createNewFile();
		      }	
		      WriteFile(Main.sFile.get(Main.sFile.size()-1),Data);
		    } catch (IOException e) {
		      e.printStackTrace();
		      return false;
		    }
		return true;
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
				"#ifndef "+full_name+"_PROXY_H_\r\n"
			      		+ "#define "+full_name+"_PROXY_H_\r\n"
			      		+ "#include <string.h>\r\n"
			      		+ "#include \"core/future.h\"\r\n"
			      		+ "#include \"com/proxy_skeleton/skeleton/service_proxy.h\"\r\n"
			      		+ "#include \"com/proxy_skeleton/definitions.h\"\r\n"
			      		+ "#include \""+name+"_returntypes.h\"\r\n"
			      		+ "#include \""+name+"_common.h\"\r\n"
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
			ArrayList<Node> args = method.Search("arguments","argument-probs");
			String m_a = "";
			for(Node arg:args) {
				String t = c_get((arg.Search("type").get(0).getVal()));
				if(t.contains("/")) {
					String inc = t.substring(0,t.lastIndexOf('/'));
					Data = Data.replace("//#include", "#include \""+inc+".h\"\r\n//#include");
					m_a+=t.substring(t.lastIndexOf('/') + 1);
				}
				else {
					m_a+=t;
				}
								
				m_a += arg.Search("direction").get(0).getVal().contains("out")? " &":" ";
				m_a += c_get((arg.Search("short-name").get(0).getVal())) + ",";
			}
			m_a = m_a.substring(0, m_a.lastIndexOf(','));
			Data+="methods::"+m_n+"_m "+ m_n +";\r\n";
		}

		Data+= "};\r\n";
		//Finish
		for(String i:sym) {
			Data+=  "}\r\n";
		}
		Data+= "#endif";
		Data = Data.replace("//#include", "");
		Main.pFile.add(Main.Direc + name + "_proxy.h");
		try {
		      File myObj = new File(Main.pFile.get(Main.sFile.size()-1));
		      if (!myObj.createNewFile()) {
		        myObj.delete();
		        myObj.createNewFile();
		      }
		      WriteFile(Main.pFile.get(Main.pFile.size()-1),Data);
		    } catch (IOException e) {
		      e.printStackTrace();
		      return false;
		    }
		return true;
	}
	
	
	public String ReadFile(String Path) throws FileNotFoundException {
		File myObj = new File(Path);
		String data = new String();
	    Scanner myReader = new Scanner(myObj);
	    while (myReader.hasNextLine()) 
	    {
	      data += myReader.nextLine()+'\n';
	    }
	    myReader.close();
	    return data;
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