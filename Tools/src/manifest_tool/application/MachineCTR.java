package application;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class MachineCTR {
	
	@FXML
	public Accordion fg_acc;
	public Button Add_Mode_Btn;
	public Button New_FG_Btn;
	public Button Del_FG_Btn;
	public Button Save_Btn;
	public Button Prev_Btn;
	public Button Next_Btn;
	public VBox container;
	public HBox indicator;
	public TextField fg_name;
	public TextField mac_id;
	public FileChooser FC = new FileChooser();
	public static ArrayList<Accordion> fg_list = new ArrayList<>();
	public static ArrayList<String> fg_names = new ArrayList<>();
	public static String manifest_id;
	public static int mode = 0;
	public static String path;
	
	public void initialize() {
		if(mode == 1) {
			mac_id.setText(manifest_id);
			if(fg_list.size()>1) {
				Del_FG_Btn.setDisable(false);
				Next_Btn.setDisable(false);
				Prev_Btn.setDisable(true);
			}
			else {
				Del_FG_Btn.setDisable(true);
				Next_Btn.setDisable(true);
				Prev_Btn.setDisable(true);
			}
			for(Accordion i:fg_list) {
				for(TitledPane ii:i.getPanes()) {
					Button del = (Button) ii.getGraphic();
					del.setOnAction(new EventHandler<ActionEvent>() {
						 @Override
						    public void handle(ActionEvent e) {
							 i.getPanes().remove(i.getPanes().indexOf(ii));
							 for(int c=0;c<i.getPanes().size();c++) {
								 TitledPane current = i.getPanes().get(c);
								 String mode_name = "mode_"+Integer.toString(c);
								 current.setText(mode_name);
							 }
						 }
					});
				}
			}
			fg_acc = fg_list.get(0);
			container.getChildren().remove(2);
			container.getChildren().add(fg_acc);
			fg_name.setText(fg_names.get(0));
			((Label)indicator.getChildren().get(0)).setText("Current Function Group: 1 of "
					+Integer.toString(fg_list.size()));
		}
		else {
			fg_list = new ArrayList<>();
			fg_names = new ArrayList<>();
			manifest_id = "MM_ID";
			mac_id.setText(manifest_id);
			fg_list.add(fg_acc);
			Del_FG_Btn.setDisable(true);
			Next_Btn.setDisable(true);
			Prev_Btn.setDisable(true);
			((Label)indicator.getChildren().get(0)).setText("Current Function Group: 1 of 1");
			fg_name.setText("new_fg");
			fg_names.add(fg_name.getText());
		}
		fg_name.textProperty().addListener((observable, oldValue, newValue) -> {
			int current = fg_list.indexOf(fg_acc);
		 	fg_names.set(current, newValue);
		});
	}
	public void Add_Mode(ActionEvent e) {
		String mode_name = "mode_"+Integer.toString(fg_acc.getPanes().size());
		TitledPane tp = new TitledPane();
		tp.setText(mode_name);
		Button delete = new Button("X");
		delete.setDefaultButton(true);
		delete.setFont(Font.font("Arial", FontWeight.BOLD, 10));
		delete.setGraphic(new TextField());
		tp.setGraphic(delete);
		tp.setGraphicTextGap(30);
		tp.setAnimated(true);
		tp.setAlignment(Pos.CENTER);
		tp.setContentDisplay(ContentDisplay.RIGHT);
		tp.setCollapsible(false);
		fg_acc.getPanes().add(tp);
		delete.setOnAction(new EventHandler<ActionEvent>() {
			 @Override
			    public void handle(ActionEvent e) {
				 fg_acc.getPanes().remove(fg_acc.getPanes().indexOf(tp));
				 for(int i=0;i<fg_acc.getPanes().size();i++) {
					 TitledPane current = fg_acc.getPanes().get(i);
					 String mode_name = "mode_"+Integer.toString(i);
					 current.setText(mode_name);
				 }
			    }
		});
	}
	public void New_FG(ActionEvent e) {
		fg_list.add(new Accordion());
		fg_names.add("new_fg");
		Next_Btn.setDisable(false);
		Del_FG_Btn.setDisable(false);
		((Label)indicator.getChildren().get(0)).setText("Current Function Group: "+ 
				Integer.toString(fg_list.indexOf(fg_acc) + 1) +" of "+Integer.toString(fg_list.size()));
	}
	public void Del_FG(ActionEvent e) {
		int current = fg_list.indexOf(fg_acc);
		fg_list.remove(current);
		fg_names.remove(current);
		if(current == fg_list.size())current--;
		fg_acc = fg_list.get(current);
		fg_name.setText(fg_names.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(fg_acc);
		if(fg_list.size()==1) {
			Prev_Btn.setDisable(true);
			Del_FG_Btn.setDisable(true);
		}
		if(current == fg_list.size()-1)Next_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Function Group: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(fg_list.size()));
	}
	public void Next_FG(ActionEvent e) {
		int current = fg_list.indexOf(fg_acc);
		current++;
		fg_acc = fg_list.get(current);
		fg_name.setText(fg_names.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(fg_acc);
		Prev_Btn.setDisable(false);
		if(current == fg_list.size()-1)Next_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Function Group: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(fg_list.size()));
	}
	public void Prev_FG(ActionEvent e) {
		int current = fg_list.indexOf(fg_acc);
		current--;
		fg_acc = fg_list.get(current);
		fg_name.setText(fg_names.get(current));
		container.getChildren().remove(2);
		container.getChildren().add(fg_acc);
		Next_Btn.setDisable(false);
		if(current==0)Prev_Btn.setDisable(true);
		((Label)indicator.getChildren().get(0)).setText("Current Function Group: "+ 
				Integer.toString(current+1) +" of "+Integer.toString(fg_list.size()));
	}
	public void Save(ActionEvent e) throws IOException {
		StringBuilder Error = new StringBuilder ();		
		Node JSONTree = Node.MM_GUIToTree(mac_id.getText(),fg_list, fg_names,Error);
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
			alert.setTitle("Machine Manifest Exportation");
			Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
			stage.getIcons().add(new Image("ok.png"));
			alert.showAndWait();
		}
		else {
			FC.setTitle("Export Machine Manifest JSON");
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
				alert.setTitle("Machine Manifest Exportation");
				Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
				stage.getIcons().add(new Image("ok.png"));
				alert.showAndWait();
				path = myObj.getPath();
				mode = 1;
				Controller.getSecondaryStage().setTitle("Machine Manifest Modify");
			}
		}
	}
}
