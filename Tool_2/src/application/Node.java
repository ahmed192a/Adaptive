package application;

import java.util.ArrayList;

import javafx.collections.ObservableList;
import javafx.scene.control.Accordion;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

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
	
	public static Node GUIToTree(String manifest_id,ArrayList<Accordion> process_list,ArrayList<String> process_name,StringBuilder Error) {
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

}










/*
public static Node ParseXML(String Data) {
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
private static String get_tag(String Data,int start) {
	int end = start;
	for(;end+1!=Data.length() && Data.charAt(end+1)!='<' && Data.charAt(end+1)!='>';end++);
	if(end + 1 == Data.length() || Data.charAt(end+1)=='<')return "ERROR";
	return Data.substring(start,end+1);
}
private static boolean hasChild(String Data,int pos) {
	while(pos!=Data.length() && Character.isWhitespace(Data.charAt(pos)))pos++;
	if(pos == Data.length() || Data.charAt(pos) == '<')return true;
	else return false;
}	
public ArrayList<Node> Search(String...strings) {
	ArrayList<Node> Res = new ArrayList<Node>();
	Node current = this;
	for (String path : strings) {
		for(Node i : current.getChilds()) {
			if(i.getTag().equals(path)) {
				if(path.equals(strings[strings.length - 1])) {
					Res.add(i);
				}
				else {
					current = i;
					break;	
				}
			}
		}
	}
    return Res;
}*/





