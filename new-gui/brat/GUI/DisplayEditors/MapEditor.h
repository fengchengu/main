#ifndef GUI_DISPLAY_EDITORS_MAP_EDITOR_H
#define GUI_DISPLAY_EDITORS_MAP_EDITOR_H


#include "AbstractDisplayEditor.h"


class CWPlot;
class CBratMapView;
class CGlobeWidget;

struct CViewControlsPanelPlots;

struct CMapControlsPanelEdit;
struct CMapControlsPanelOptions;




/////////////////////////////////////////////////////////////////
//	TODO: move to proper place after using real projections
/////////////////////////////////////////////////////////////////

QActionGroup* ProjectionsActions( QWidget *parent );





/////////////////////////////////////////////////////////////////
//						Map Editor
/////////////////////////////////////////////////////////////////



class CMapEditor : public CAbstractDisplayEditor
{
#if defined (__APPLE__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

	Q_OBJECT;

#if defined (__APPLE__)
#pragma clang diagnostic pop
#endif

	// types


	using base_t = CAbstractDisplayEditor;


	// instance data

	//map && globe
	CBratMapView *mMapView = nullptr;
	CGlobeWidget *mGlobeView = nullptr;
	//
	//...map/globe managed widgets/actions
	QProgressBar *mProgressBar = nullptr;
	QCheckBox *mRenderSuppressionCBox = nullptr;

	QAction *mActionMeasure = nullptr;
	QAction *mActionMeasureArea = nullptr;
	QToolButton *mMeasureButton = nullptr;
	QAction *mActionDecorationGrid = nullptr;


	//...actions
	QAction *mActionStatisticsMean = nullptr;
	QAction *mActionStatisticsStDev = nullptr;
	QAction *mActionStatisticsLinearRegression = nullptr;
	QToolButton *mToolProjection = nullptr;

	QActionGroup *mProjectionsGroup;

	//...tabs
	CMapControlsPanelEdit *mTabData = nullptr;
	CMapControlsPanelOptions *mTabView = nullptr;
	CViewControlsPanelPlots *mTabPlots = nullptr;


	// construction /destruction

private:
	void CreateMapActions();
	void CreateAndWireNewMap();
	void CreateWidgets();
	void WireMapActions();
	void Wire();

public:
    CMapEditor( CModel *model, COperation *operation, QWidget *parent = nullptr );
    CMapEditor( CDisplayFilesProcessor *proc, CWPlot* wplot, QWidget *parent = nullptr );

	virtual ~CMapEditor();

	// 

protected:
	virtual void ResetViews() override;


	virtual void Show2D( bool checked ) override;
	virtual void Show3D( bool checked ) override;

	virtual void PlotChanged( int index ) override;
	virtual void NewButtonClicked() override;

	virtual void DatasetsIndexChanged( int index ) override;
	virtual void FiltersIndexChanged( int index ) override;

	virtual void OneClick() override;

protected slots:

	void HandleStatisticsMean();
	void HandleStatisticsStDev();
	void HandleStatisticsLinearRegression();

	void HandleProjection();
};





#endif			// GUI_DISPLAY_EDITORS_MAP_EDITOR_H