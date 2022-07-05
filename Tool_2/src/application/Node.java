package application;

import java.util.ArrayList;

import javafx.collections.ObservableList;
import javafx.geometry.Pos;
import javafx.scene.control.Accordion;
import javafx.scene.control.Button;
import javafx.scene.control.ContentDisplay;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class Node {
	
	enum Types {value, element,array}
	private Node parent;
	private String tag;
	private String val;
	private Types type;
	private ArrayList<Node> childs = new ArrayList<Node>();
	
	public Node getParent() {return parent;}
	public Node(Node parent,String name,String value) {
		this.parent = parent;
		this.tag = name;
		this.val = value;
		this.type = Types.value;
	}
	public Node(Node parent,String name,int isArray) {
		this.parent = parent;
		this.tag = name;
		if(isArray == 0)this.type = Types.element;
		else this.type = Types.array;	
	}
	public Node addNode(Node child) {
		childs.add(child);
		return child;
	}
	public ArrayList<Node> getChilds() {
		return childs;
	}
	public String getTag() {
		return tag;
	}
	public String getVal() {
		return val;
	}
	public String getType() {
		return type.name();
	}
	
	public static Node EM_GUIToTree(String manifest_id,ArrayList<Accordion> process_list,ArrayList<String> process_name,StringBuilder Error) {
		Node root = new Node(null,"",0);  
		Node current = root.addNode(new Node(root,"Execution_manifest",0));
		if(manifest_id.equals("")) {
			Error.append("Manifest ID Missing!");
			return null;
		}
		current.addNode(new Node(current,"Execution_manifest_id",manifest_id));
		current = current.addNode(new Node(current,"Process",1));
		for(int i=0;i<process_list.size();i++) {
			current = current.addNode(new Node(current,"",0));
			if(process_name.get(i).equals("")) {
				Error.append("Process no."+ i +" Name is Missing!");
				return null;
			}
			if(process_name.indexOf(process_name.get(i))!=process_name.lastIndexOf(process_name.get(i))) {
				Error.append("Process Name \""+ process_name.get(i) +"\" is Duplicated!");
				return null;
			}
			current.addNode(new Node(current,"Process_name",process_name.get(i)));
			ObservableList<TitledPane> cfgs = process_list.get(i).getPanes();
			if(cfgs.size()<1) {
				Error.append("Process Name \""+ process_name.get(i) +"\" Should Have At Least One Startup Config!");
				return null;
			}
			current = current.addNode(new Node(current,"Mode_dependent_startup_configs",1));
			for(int ii=0;ii<cfgs.size();ii++) {
				current = current.addNode(new Node(current,"",0));
				Accordion cfg =  (Accordion)cfgs.get(ii).getContent();
				ObservableList<TitledPane> all = cfg.getPanes();				
				for(int iii=0;iii<all.size();iii++) {
					if(all.get(iii).getText().charAt(0)=='f')break;
					if(!current.getTag().equals("Startup_options"))current = current.addNode(new Node(current,"Startup_options",1));
					current = current.addNode(new Node(current,"",0));		
					VBox vb = (VBox)all.get(iii).getContent();
					String s1 = ((TextField)((HBox)vb.getChildren().get(0)).getChildren().get(1)).getText();
					String s2 = ((TextField)((HBox)vb.getChildren().get(1)).getChildren().get(1)).getText();
					String s3 = ((TextField)((HBox)vb.getChildren().get(2)).getChildren().get(1)).getText();
					current.addNode(new Node(current,"Option_kind",s1));
					current.addNode(new Node(current,"Option_name",s2));
					current.addNode(new Node(current,"Option_arg",s3));
					current = current.getParent();
				}
				if(current.getTag().equals("Startup_options"))current = current.getParent();
				for(int iii=0;iii<all.size();iii++) {
					if(all.get(iii).getText().charAt(0)=='s')continue;
					if(!current.getTag().equals("FunctionGroupDependencies"))current = current.addNode(new Node(current,"FunctionGroupDependencies",1));
					current = current.addNode(new Node(current,"",0));		
					VBox vb = (VBox)all.get(iii).getContent();
					String s1 = ((TextField)((HBox)vb.getChildren().get(0)).getChildren().get(1)).getText();
					String s2 = ((TextField)((HBox)vb.getChildren().get(1)).getChildren().get(1)).getText();
					if(s1.equals("")||s2.equals("")) {
						Error.append("Process Name \""+ process_name.get(i) +"\" FG Dependency Data is Empty!");
						return null;
					}
					current.addNode(new Node(current,"Function_group",s1));
					current.addNode(new Node(current,"Modes",s2));
					current = current.getParent();
				}
				if(current.getTag().equals("FunctionGroupDependencies"))current = current.getParent();
				else {
					Error.append("Process Name \""+ process_name.get(i) +"\" Should Have At Least One FG Dependency!");
					return null;
				}
				current = current.getParent();
			}
			current = current.getParent();
			current = current.getParent();
		}
		return root;
	}
	public static Node MM_GUIToTree(String manifest_id,ArrayList<Accordion> fg_list,ArrayList<String> fg_names,StringBuilder Error) {
		Node root = new Node(null,"",0);  
		Node current = root.addNode(new Node(root,"Machine_manifest",0));
		if(manifest_id.equals("")) {
			Error.append("Manifest ID Missing!");
			return null;
		}
		current.addNode(new Node(current,"Machine_manifest_id",manifest_id));
		current = current.addNode(new Node(current,"Mode_declaration_group",1));
		for(int i=0;i<fg_list.size();i++) {
			current = current.addNode(new Node(current,"",0));
			if(fg_names.get(i).equals("")) {
				Error.append("FG no."+ i +" Name is Missing!");
				return null;
			}
			if(fg_names.indexOf(fg_names.get(i))!=fg_names.lastIndexOf(fg_names.get(i))) {
				Error.append("FG Name \""+ fg_names.get(i) +"\" is Duplicated!");
				return null;
			}
			current.addNode(new Node(current,"Function_group_name",fg_names.get(i)));
			ObservableList<TitledPane> modes = fg_list.get(i).getPanes();
			if(modes.size()<1) {
				Error.append("FG Name \""+ fg_names.get(i) +"\" Should Have At Least One Mode!");
				return null;
			}
			current = current.addNode(new Node(current,"Mode_declarations",1));
			for(int ii=0;ii<modes.size();ii++) {
				Node mode = new Node(current,"",0);
				mode.addNode(new Node(current,"Mode",
						((TextField)((Button)modes.get(ii).getGraphic()).getGraphic()).getText()));
				current.addNode(mode);
			}
			current = current.getParent();
			current = current.getParent();
		}
		return root;
	}
	public static String TreeToJSON(String Data,ArrayList<Node> row,int lvl) {
		for(Node node:row) {
			//Value
			if((!node.getTag().equals(""))&&node.getVal()!=null) {		
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+="\""+node.getTag()+"\": \""+node.getVal()+"\"";
			}
			//Array Or Element
			else {			
				for(int i=0;i<lvl;i++)Data+="\t";
				if(node.getTag()!="")Data+="\""+node.getTag()+"\": ";
				//which ? Array Or Single Element
				Data+=(node.getType()=="element")? "{\n":"[\n";
				Data = TreeToJSON(Data,node.getChilds(),lvl+1);
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+=(node.getType()=="element")? "}":"]";
			}
			if(row.indexOf(node)!=row.size()-1)Data+=",";
			Data+="\n";
		}
		return Data;
	}
	public static Node JSONToTree(String Data) {
		Node JSONTree=new Node(null,"root",1),Current=JSONTree;
		int Ptr = 0;
		boolean g2c = false;
		while(Ptr < Data.length()) {
			if(Character.isWhitespace(Data.charAt(Ptr)));	//Whitespace
			else if(Data.charAt(Ptr)==',') {
				if(g2c==false)return null; 					//Duplicated Comma or in wrong place
				g2c = false;								//Comma (More Elements)
			}
			else if(Data.charAt(Ptr)=='{') {				//Element With No Tag
				if(g2c||!Current.getType().equals("array"))return null;
				Current = Current.addNode(new Node(Current,"",0));
			}
			else if(Data.charAt(Ptr)=='"') {				//Value Or Element Or Array
				if(g2c||!Current.getType().equals("element"))return null;
				int begin = ++Ptr;
				while(Ptr < Data.length() && Data.charAt(Ptr)!='"') Ptr++;
				if(Ptr==Data.length())return null;
				String tag = Data.substring(begin,Ptr);
				if(tag.length()==0)return null;
				Ptr++;
				while(Ptr < Data.length() && Character.isWhitespace(Data.charAt(Ptr)))Ptr++;
				if(Ptr==Data.length())return null;
				if(Data.charAt(Ptr)!=':')return null;
				Ptr++;
				while(Ptr < Data.length() && Character.isWhitespace(Data.charAt(Ptr)))Ptr++;
				if(Ptr==Data.length())return null;
				if(Data.charAt(Ptr)=='"') {
					begin = ++Ptr;
					while(Ptr < Data.length() && Data.charAt(Ptr)!='"') Ptr++;
					if(Ptr==Data.length())return null;
					String val = Data.substring(begin,Ptr);
					Current.addNode(new Node(Current,tag,val));
					g2c = true;
				}
				else if(Data.charAt(Ptr)=='{') {
					Current = Current.addNode(new Node(Current,tag,0));
				}
				else if(Data.charAt(Ptr)=='[') {
					Current = Current.addNode(new Node(Current,tag,1));
				}
				else return null;
			}
			else if(Data.charAt(Ptr)=='}') {				//Close Element
				if(!g2c || !Current.getType().equals("element"))return null;
				else Current = Current.getParent();	
			}
			else if(Data.charAt(Ptr)==']') {				//Close Array
				if(!g2c || !Current.getType().equals("array"))return null;
				else Current = Current.getParent();
			}
			else return null;
			Ptr++;
		}
		return (JSONTree==Current && JSONTree.getChilds().size()!=0)?JSONTree.getChilds().get(0):null;
	}
	public static GUI TreeToGUI(Node Tree) {
		if(!Tree.getTag().equalsIgnoreCase("")||!Tree.getType().equals("element"))return null;
		Node Current = Tree;
		ArrayList<Node> Search;
		/////Data To Be Filled/////////
		GUI res = new GUI();
		///////////////////////////////
		Search = Current.Search("Execution_manifest");
		if(Search.size()==0)	return null;
		Current = Search.get(0);
		
		Search = Current.Search("Execution_manifest_id");
		if(Search.size()==0||Search.get(0).getVal()==null) res.manifest_id = "";
		else res.manifest_id = Search.get(0).getVal();

		Search = Current.Search("Process");
		if(Search.size()==0)	return null;
		Current = Search.get(0);
		if(!Current.getType().equals("array"))	return null;
		
		ArrayList<Node> processes = Current.getChilds();
		for(Node process:processes) { // Process is "" tag
			//Use Search From Here
			res.process_list.add(new Accordion());
			Search = process.Search("Process_name");
			if(Search.size()==0||Search.get(0).getVal()==null) res.process_name.add("");
			else res.process_name.add(Search.get(0).getVal());

			Search = process.Search("Mode_dependent_startup_configs");
			if(Search.size()!=0) {	
				Current = Search.get(0);
				if(!Current.getType().equals("array"))	return null;
				ArrayList<Node> cfgs = Current.getChilds();
				for(Node cfg:cfgs) {
					String cfg_name = "startup_config_"+Integer.toString(cfgs.indexOf(cfg));
					TitledPane tp = new TitledPane();
					tp.setText(cfg_name);
					Button delete = new Button("X");
					delete.setDefaultButton(true);
					delete.setFont(Font.font("Arial", FontWeight.BOLD, 10));
					tp.setGraphic(delete);
					tp.setGraphicTextGap(30);
					tp.setAnimated(true);
					tp.setAlignment(Pos.TOP_LEFT);
					tp.setContentDisplay(ContentDisplay.RIGHT);
					res.process_list.get(res.process_list.size()-1).getPanes().add(tp);
					Accordion Content = new Accordion();
					Content.setMaxSize(Region.USE_PREF_SIZE, Region.USE_PREF_SIZE);
					
					Search = cfg.Search("Startup_options");
					if(Search.size()!=0) {	
						Current = Search.get(0);
						if(!Current.getType().equals("array"))	return null;
						ArrayList<Node> ops = Current.getChilds();
						for(Node op:ops) {
							
							Button delete_op = new Button("X");
							delete_op.setDefaultButton(true);
							delete_op.setFont(Font.font("Arial", FontWeight.BOLD, 10));
							
							TitledPane otp = new TitledPane();
							otp.setText("startup_option_"+Integer.toString(ops.indexOf(op)));
							otp.setGraphic(delete_op);
							otp.setGraphicTextGap(25);
							otp.setAnimated(true);
							otp.setAlignment(Pos.TOP_CENTER);
							otp.setContentDisplay(ContentDisplay.RIGHT);
							
							String Option_kind,Option_name,Option_arg;
							
							if(op.Search("Option_kind").size()==0
									||op.Search("Option_kind").get(0).getVal()==null)Option_kind="";
							else Option_kind = op.Search("Option_kind").get(0).getVal();

							if(op.Search("Option_name").size()==0
									||op.Search("Option_name").get(0).getVal()==null)Option_name="";
							else Option_name = op.Search("Option_name").get(0).getVal();
							
							if(op.Search("Option_arg").size()==0
									||op.Search("Option_arg").get(0).getVal()==null)Option_arg="";
							else Option_arg = op.Search("Option_arg").get(0).getVal();
							
							VBox options = new VBox();
							HBox o1 = new HBox();
							HBox o2 = new HBox();
							HBox o3 = new HBox();
							o1.getChildren().addAll(new Label("option_kind"),new TextField(Option_kind));
							o1.setSpacing(20);
							o2.getChildren().addAll(new Label("option_name"),new TextField(Option_name));
							o2.setSpacing(10);
							o3.getChildren().addAll(new Label("option_arg"),new TextField(Option_arg));
							o3.setSpacing(20);
							options.getChildren().addAll(o1,o2,o3);
							otp.setContent(options);
							Content.getPanes().add(otp);
						}
					}
					Search = cfg.Search("FunctionGroupDependencies");
					if(Search.size()!=0) {	
						Current = Search.get(0);
						if(!Current.getType().equals("array"))	return null;
						ArrayList<Node> deps = Current.getChilds();
						for(Node dep:deps) {
							
								
							Button delete_dep = new Button("X");
							delete_dep.setDefaultButton(true);
							delete_dep.setFont(Font.font("Arial", FontWeight.BOLD, 10));
							
							TitledPane dtp = new TitledPane();
							dtp.setText("fg_dependency_"+Integer.toString(deps.indexOf(dep)));
							dtp.setGraphic(delete_dep);
							dtp.setGraphicTextGap(25);
							dtp.setAnimated(true);
							dtp.setAlignment(Pos.TOP_CENTER);
							dtp.setContentDisplay(ContentDisplay.RIGHT);
							
							String Function_group,Modes;
							
							if(dep.Search("Function_group").size()==0
									||dep.Search("Function_group").get(0).getVal()==null)Function_group="";
							else Function_group = dep.Search("Function_group").get(0).getVal();

							if(dep.Search("Modes").size()==0
									||dep.Search("Modes").get(0).getVal()==null)Modes="";
							else Modes = dep.Search("Modes").get(0).getVal();
							
							
							VBox options = new VBox();
							HBox o1 = new HBox();
							HBox o2 = new HBox();
							o1.getChildren().addAll(new Label("fg_name"),new TextField(Function_group));
							o1.setSpacing(20);
							o2.getChildren().addAll(new Label("modes"),new TextField(Modes));
							o2.setSpacing(30);
							options.getChildren().addAll(o1,o2);
							dtp.setContent(options);
							Content.getPanes().add(dtp);	
						}
					}
					
					tp.setContent(Content);
				}
			}
		}
		return res;
	}
	
	public ArrayList<Node> Search(String...strings) {
		ArrayList<Node> Res = new ArrayList<Node>();
		Node current = this;
		for (String path : strings) {
			boolean found = false;
			for(Node i : current.getChilds()) {
				if(i.getTag().equalsIgnoreCase(path)) {
					found = true;
					if(path.equals(strings[strings.length - 1])) {
						Res.add(i);
					}
					else {
						current = i;
						break;	
					}
				}
			}
			if(!found)return Res;
		}
	    return Res;
	}
	
}

















