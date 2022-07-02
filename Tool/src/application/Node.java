package application;

import java.util.ArrayList;

import javafx.collections.ObservableList;
import javafx.scene.control.Accordion;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class Node {
	private Node parent;
	private String tag;
	private String val;
	private boolean isParent;
	private ArrayList<Node> childs = new ArrayList<Node>();
	
	public Node getParent() {
		return parent;
	}
	public Node(Node parent,String name,String value) {
		this.parent = parent;
		this.tag = name;
		this.val = value;
		this.isParent = false;
	}
	public Node(Node parent,String name) {
		this.parent = parent;
		this.tag = name;
		this.isParent = true;
	}
	public Node addNode(Node child) {
		childs.add(child);
		return child;
	}
	public boolean isParent() {
		return isParent;
	}
	public String getTag() {
		return tag;
	}
	public ArrayList<Node> getChilds() {
		return childs;
	}
	public String getVal() {
		return val;
	}
	
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
	}
	

	
	
	
	
	public static Node GUIToTree(String manifest_id,ArrayList<Accordion> process_list,ArrayList<String> process_name,StringBuilder Error) {
		Node root = new Node(null,"");  
		Node current = root.addNode(new Node(root,"Execution_manifest"));
		if(manifest_id.equals("")) {
			Error.append("Manifest ID Missing!");
			return null;
		}
		current.addNode(new Node(current,"Execution_manifest_id",manifest_id));
		current = current.addNode(new Node(current,"Process"));
		for(int i=0;i<process_list.size();i++) {
			current = current.addNode(new Node(current,""));
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
			current = current.addNode(new Node(current,"Mode_dependent_startup_configs"));
			for(int ii=0;ii<cfgs.size();ii++) {
				current = current.addNode(new Node(current,""));
				Accordion cfg =  (Accordion)cfgs.get(ii).getContent();
				ObservableList<TitledPane> all = cfg.getPanes();				
				for(int iii=0;iii<all.size();iii++) {
					if(all.get(iii).getText().charAt(0)=='f')break;
					if(!current.getTag().equals("Startup_options"))current = current.addNode(new Node(current,"Startup_options"));
					current = current.addNode(new Node(current,""));		
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
					if(!current.getTag().equals("FunctionGroupDependencies"))current = current.addNode(new Node(current,"FunctionGroupDependencies"));
					current = current.addNode(new Node(current,""));		
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
			//ArrayElement
			else if(node.getTag().equals("")){		
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+="{\n";
				Data = TreeToJSON(Data,node.getChilds(),lvl+1);
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+="}";			
			}
			//Either Array Or Single Element
			else {			
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+="\""+node.getTag()+"\": ";
				//which ? Array Or Single Element
				Data+=(node.getChilds().size()==0||node.getChilds().get(0).getTag()!="")? "{\n":"[\n";
				Data = TreeToJSON(Data,node.getChilds(),lvl+1);
				for(int i=0;i<lvl;i++)Data+="\t";
				Data+=(node.getChilds().size()==0||node.getChilds().get(0).getTag()!="")? "}":"]";
			}
			if(row.indexOf(node)!=row.size()-1)Data+=",";
			Data+="\n";
		}
		return Data;
	}




}
