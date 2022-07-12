package application;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class ExecutionCTR {
	
	@FXML
	public Accordion process_acc;
	public Button Add_Cfg_Btn;
	public Button Add_Op_Btn;
	public Button Add_Dep_Btn;
	public Button New_Proc_Btn;
	public Button Del_Proc_Btn;
	public Button Save_Btn;
	public Button Prev_Btn;
	public Button Next_Btn;
	public VBox container;
	public HBox indicator;
	public TextField p_name;
	public TextField exec_id;
	public FileChooser FC = new FileChooser();
	public static ArrayList<Accordion> process_list = new ArrayList<>();
	public static ArrayList<String> process_name = new ArrayList<>();
	public static String manifest_id;
	public static int mode = 0;
	public static String path;
	
	public void initialize() {
		if(mode == 1) {
			exec_id.setText(manifest_id);
			if(process_list.size()>1) {
				Del_Proc_Btn.setDisable(false);
				Next_Btn.setDisable(false);
				Prev_Btn.setDisable(true);
			}
			else {
				Del_Proc_Btn.setDisable(true);
				Next_Btn.setDisable(true);
				Prev_Btn.setDisable(true);
			}
			for(Accordion i:process_list) {
				for(TitledPane ii:i.getPanes()) {
					Button del = (Button) ii.getGraphic();
					del.setOnAction(new EventHandler<ActionEvent>() {
						 @Override
						    public void handle(ActionEvent e) {
							 i.getPanes().remove(i.getPanes().indexOf(ii));
							 for(int c=0;c<i.getPanes().size();c++) {
								 TitledPane current = i.getPanes().get(c);
								 String cfg_name = "startup_config_"+Integer.toString(c);
								 current.setText(cfg_name);
							 }
						 }
					});
					for(TitledPane iii:((Accordion)ii.getContent()).getPanes()) {
						Button del2 = (Button) iii.getGraphic();
						del2.setOnAction(new EventHandler<ActionEvent>() {
							 @Override
							    public void handle(ActionEvent e) {
								 ((Accordion)ii.getContent()).getPanes()
								 	.remove(((Accordion)ii.getContent()).getPanes().indexOf(iii));
								 int index = 0;
									while(index<((Accordion)ii.getContent()).getPanes().size() && 
											((Accordion)ii.getContent()).getPanes().get(index).getText().charAt(0) == 's') {
										((Accordion)ii.getContent()).getPanes().get(index).setText("startup_option_"+Integer.toString(index));
										 index++;
									}
									 int offset = index;
										while(index<((Accordion)ii.getContent()).getPanes().size() && 
												((Accordion)ii.getContent()).getPanes().get(index).getText().charAt(0) == 'f') {
											((Accordion)ii.getContent()).getPanes().get(index).setText("fg_dependency_"+Integer.toString(index-offset));
											 index++;
										}
									
									
									
							    }
						});
					}
				}
			}
			process_acc = process_list.get(0);
			container.getChildren().remove(2);
			container.getChildren().add(process_acc);
			p_name.setText(process_name.get(0));
			((Label)indicator.getChildren().get(0)).setText("Current Process: 1 of "
					+Integer.toString(process_list.size()));
		}
		else {
			process_list = new ArrayList<>();
			process_name = new ArrayList<>();
			manifest_id = "new_manifest";
			exec_id.setText(manifest_id);
			process_list.add(process_acc);
			Del_Proc_Btn.setDisable(true);
			Next_Btn.setDisable(true);
			Prev_Btn.setDisable(true);
			((Label)indicator.getChildren().get(0)).setText("Current Process: 1 of 1");
			p_name.setText("new_process");
			process_name.add(p_name.getText());
		}
		p_name.textProperty().addListener((observable, oldValue, newValue) -> {
			int current = process_list.indexOf(process_acc);
		 	process_name.set(current, newValue);
		});
	}
	public void Add_Cfg(ActionEvent e) {
		String cfg_name = "startup_config_"+Integer.toString(process_acc.getPanes().size());
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
		process_acc.getPanes().add(tp);
		delete.setOnAction(new EventHandler<ActionEvent>() {
			 @Override
			    public void handle(ActionEvent e) {
				 process_acc.getPanes().remove(process_acc.getPanes().indexOf(tp));
				 for(int i=0;i<process_acc.getPanes().size();i++) {
					 TitledPane current = process_acc.getPanes().get(i);
					 String cfg_name = "startup_config_"+Integer.toString(i);
					 current.setText(cfg_name);
				 }
			    }
		});
		Accordion Content = new Accordion();
		Content.setMaxSize(Region.USE_PREF_SIZE, Region.USE_PREF_SIZE);
		tp.setContent(Content);
	}
	public void Add_Op(ActionEvent e) {
		TitledPane selected = process_acc.getExpandedPane();
		if(selected == null)return;
		Accordion content = (Accordion) selected.getContent();
		ObservableList<TitledPane> panes = content.getPanes();
		int index = 0;
		while(index<panes.size() && panes.get(index).getText().charAt(0) == 's')index++;
		
		Button delete_op = new Button("X");
		delete_op.setDefaultButton(true);
		delete_op.setFont(Font.font("Arial", FontWeight.BOLD, 10));
		
		TitledPane op = new TitledPane();
		op.setText("startup_option_"+Integer.toString(index));
		op.setGraphic(delete_op);
		op.setGraphicTextGap(25);
		op.setAnimated(true);
		op.setAlignment(Pos.TOP_CENTER);
		op.setContentDisplay(ContentDisplay.RIGHT);
		
		VBox options = new VBox();
		HBox o1 = new HBox();
		HBox o2 = new HBox();
		HBox o3 = new HBox();
		o1.getChildren().addAll(new Label("option_kind"),new TextField());
		o1.setSpacing(20);
		o2.getChildren().addAll(new Label("option_name"),new TextField());
		o2.setSpacing(10);
		o3.getChildren().addAll(new Label("option_arg"),new TextField());
		o3.setSpacing(20);
		options.getChildren().addAll(o1,o2,o3);
		op.setContent(options);
		delete_op.setOnAction(new EventHandler<ActionEvent>() {
			 @Override
			    public void handle(ActionEvent e) {
				 content.getPanes().remove(content.getPanes().indexOf(op));
				 int index = 0;
					while(index<content.getPanes().size() && 
							content.getPanes().get(index).getText().charAt(0) == 's') {
						 content.getPanes().get(index).setText("startup_option_"+Integer.toString(index));
						 index++;
					}
			    }
		});
		content.getPanes().add(index, op);
	}
	public void Add_Dep(ActionEvent e) {
		TitledPane selected = process_acc.getExpandedPane();
		if(selected == null)return;
		Accordion content = (Accordion) selected.getContent();
		ObservableList<TitledPane> panes = content.getPanes();
		int index = 0,offset;
		while(index<panes.size() && panes.get(index).getText().charAt(0) == 's')index++;
		offset = index;
		while(index<panes.size() && panes.get(index).getText().charAt(0) == 'f')index++;
		index = index - offset;
		Button delete_dep = new Button("X");
		delete_dep.setDefaultButton(true);
		delete_dep.setFont(Font.font("Arial", FontWeight.BOLD, 10));
		
		TitledPane dep = new TitledPane();
		dep.setText("fg_dependency_"+Integer.toString(index));
		dep.setGraphic(delete_dep);
		dep.setGraphicTextGap(25);
		dep.setAnimated(true);
		dep.setAlignment(Pos.TOP_CENTER);
		dep.setContentDisplay(ContentDisplay.RIGHT);
		
		VBox options = new VBox();
		HBox o1 = new HBox();
		HBox o2 = new HBox();
		o1.getChildren().addAll(new Label("fg_name"),new TextField());
		o1.setSpacing(20);
		o2.getChildren().addAll(new Label("modes"),new TextField());
		o2.setSpacing(30);
		options.getChildren().addAll(o1,o2);
		dep.setContent(options);
		delete_dep.setOnAction(new EventHandler<ActionEvent>() {
			 @Override
			    public void handle(ActionEvent e) {
				 content.getPanes().remove(content.getPanes().indexOf(dep));
				 int index = 0,offset;
				 while(index<content.getPanes().size() && 
							content.getPanes().get(index).getText().charAt(0) == 's')index++;
				 offset = index;
					while(index<content.getPanes().size() && 
							content.getPanes().get(index).getText().charAt(0) == 'f') {
						 content.getPanes().get(index).setText("fg_dependency_"+Integer.toString(index-offset));
						 index++;
					}
			    }
		});
		content.getPanes().add(panes.size(), dep);
	}
	public void New_Proc(ActionEvent e) {
		process_list.add(new Accordion());
		process_name.add("new_process");
		Next_Btn.setDisable(false);
		Del_Proc_Btn.setDisable(false);
		((Label)indicator.getChildren().get(0)).setText("Current Process: "+ 
				Integer.toString(process_list.indexOf(process_acc) + 1) +" of "+Integer.toString(process_list.size()));
	}
	public void Del_Proc(ActionEvent e) {
		int current = process_list.indexOf(process_acc);
		process_list.remove(current);
		process_name.remove(current);
		if(current == process_list.size())current--;
		process_acc = process_list.get(current);
		p_name.setText(process_name.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(process_acc);
		if(process_list.size()==1) {
			Prev_Btn.setDisable(true);
			Del_Proc_Btn.setDisable(true);
		}
		if(current == process_list.size()-1)Next_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Process: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(process_list.size()));
	}
	public void Next_Proc(ActionEvent e) {
		int current = process_list.indexOf(process_acc);
		current++;
		process_acc = process_list.get(current);
		p_name.setText(process_name.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(process_acc);
		Prev_Btn.setDisable(false);
		if(current == process_list.size()-1)Next_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Process: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(process_list.size()));
	}
	public void Prev_Proc(ActionEvent e) {
		int current = process_list.indexOf(process_acc);
		current--;
		process_acc = process_list.get(current);
		p_name.setText(process_name.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(process_acc);
		Next_Btn.setDisable(false);
		if(current==0)Prev_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Process: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(process_list.size()));
	}
	public void Save(ActionEvent e) throws IOException {
		StringBuilder Error = new StringBuilder ();		
		Node JSONTree = Node.EM_GUIToTree(exec_id.getText(),process_list, process_name,Error);
		if(JSONTree == null) {
			String msg = Error.toString();
			Alert alert = new Alert(AlertType.WARNING,"Please Solve issues and Retry",ButtonType.OK);
			alert.setHeaderText(msg);
			Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
			stage.getIcons().add(new Image("warn.png"));
			alert.show();
			return;
		}
		ArrayList<Node> row = new ArrayList<>();
		row.add(JSONTree);
		String Data = Node.TreeToJSON("",row, 0);
		if(mode==1) {
			File myObj = new File(path);
			PrintWriter myWriter = new PrintWriter(myObj);
			myWriter.println(Data);
			myWriter.close();
			Alert alert = new Alert(AlertType.INFORMATION,"Path: "+myObj.getPath(),ButtonType.OK);
			alert.setHeaderText("File Overwritten Successfully");
			alert.setTitle("Execution Manifest Exportation");
			Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
			stage.getIcons().add(new Image("ok.png"));
			alert.showAndWait();
		}
		else {
			FC.setTitle("Export Execution Manifest JSON");
			FC.setInitialFileName(JSONTree.getChilds().get(0).getChilds().get(0).getVal());
			FC.getExtensionFilters().clear();
			FC.getExtensionFilters().add(new FileChooser.ExtensionFilter("json File","*.json"));			
			File myObj = FC.showSaveDialog(Main.getPrimaryStage());
			if(myObj!=null) {
				PrintWriter myWriter = new PrintWriter(myObj);
				myWriter.println(Data);
				myWriter.close();
				Alert alert = new Alert(AlertType.INFORMATION,"Path: "+myObj.getPath(),ButtonType.OK);
				alert.setHeaderText("File Saved Successfully");
				alert.setTitle("Execution Manifest Exportation");
				Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
				stage.getIcons().add(new Image("ok.png"));
				alert.showAndWait();
				path = myObj.getPath();
				mode = 1;
				Controller.getSecondaryStage().setTitle("Execution Manifest Modify");
			}
		}
	}
}
