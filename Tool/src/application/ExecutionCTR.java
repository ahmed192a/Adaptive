package application;

import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

public class ExecutionCTR {
	
	@FXML
	public Accordion process_acc;
	public Button Add_Cfg_Btn;
	public Button Add_Op_Btn;

	public void initialize() {
	
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
					 String cfg_name = "startup_config_-"+Integer.toString(i);
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

}
